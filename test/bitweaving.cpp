// Copyright (c) 2015 Flowgrammable.org
// All rights reserved

#include "../libmatch/basic_trie.cpp"

#include <iostream>
#include <new>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <chrono>
#include <algorithm>
#include <functional>
#include <stdlib.h> // exit, EXIT_FAILURE

using namespace std;
using  ns = chrono::nanoseconds;
using  ms = chrono::microseconds;
using get_time = chrono::steady_clock ;

struct Result {
  // define the result struct for merging algorithm
  int flag = -1; // show the different bit position
  int dif = 0; // the number bit of difference
};

// Matches integer type
Rule strTint(string rulestr)
{
  Rule rule;
  rule.mask = 0;
  rule.value = 0;
  // Find the position of ".", which spilit IP address to 4 parts
  size_t p1 = rulestr.find_first_of(" ");

  string substr1 = rulestr.substr(0,p1);
  string substr2 = rulestr.substr((p1 + 1));


  rule.value = stoull(substr1); // unsigned long long 64bit
  rule.mask = stoull(substr2);

  return rule;
}

/*
 * Check the mask part relation
 * whether is subset
 * the "1" bit position
*/

bool is_subset(Rule a, Rule b)
{
  vector<int> vec_a;
  vector<int> vec_b;
  // Get the "1" bit position for the mask part of two rules
  for (int i = 0; i < 64; i++) {
    if ((a.mask & (uint64_t(1) << i)) == 1) {
      vec_a.push_back(i);
    }
    if ((b.mask & (uint64_t(1) << i)) == 1) {
      vec_b.push_back(i);
    }
  }
  // Check the vec_a and vec_b is subset or not
  std::sort(vec_a.begin(),vec_a.end());
  std::sort(vec_b.begin(),vec_b.end());
  if (std::includes (vec_a.begin(), vec_a.end(), vec_b.begin(),vec_b.end())
      || std::includes (vec_b.begin(), vec_b.end(), vec_a.begin(),vec_a.end())) {
    return true;
  }
  else {
    return false;
  }
}


/*
 * Merge the rules between the first rule and second rule
 * depends on the bits of every column
 * if in each column, it has "1" and "0" or "*"
*/
Result is_mergeable(Rule firstrule, Rule secondrule)
{
  Result ret;
  Rule rule1;
  rule1.mask = firstrule.mask | secondrule.mask;
  //cout << "rule1.mask = " << rule1.mask << endl;
  if (rule1.mask == 0) {
    // Check the value part is the same or not, because there is no "*"
    for (int q = 0; q < 64; q++) {
      // Check every bit position on the value part
      if ((firstrule.value & (uint64_t(1) << q)) != (secondrule.value & (uint64_t(1) << q)) ) {
        // If the bit position are not the same, flag and dif value changes
        ret.flag = q; // show the bit position
        ret.dif++;
      }
      else {
        continue;
      }
    }
    // Get all the difference bit position between two rules (mask value = 0)
  }
  else {
    // If the mask value is not 0, which means the mask value part has the "*", wildcard
    for (int k = 0; k < 64; k++) {
      // Get all the bit positions of "0" in mask value part
      if ((rule1.mask & (uint64_t(1) << k)) == 0) {
        // check the value part, the hamming distance
        // Check the hamming distance between the value part in the "0" positions
        if ((firstrule.value & (uint64_t(1) << k)) != (secondrule.value & (uint64_t(1) << k)) ) {
          ret.flag = k; // show the bit position
          ret.dif++;
        }
        else {
          continue;
        }
      }
      else {
        continue;
      }
    }
  }
  return ret;
  // The condition for merging, hamming distance smaller than 1
}


vector<Rule> merge_rules(vector<Rule>& ruleList)
{
  // Copy into a new vector
  vector<Rule> new_rule_list(ruleList);
  Rule newRule7;
  for (int i = 0; i < new_rule_list.size() - 1; i++) {
    for (int j = i+1; j < new_rule_list.size(); j++) {
      // The condition for able to merging
      // If the two rules' mask value part is the same

      if (new_rule_list.at(i).action == new_rule_list.at(j).action) {

        if (new_rule_list.at(i).mask == new_rule_list.at(j).mask) {
          // Just compare the value part when the mask part is "0", ignor the "1" part
          Result ret2 = is_mergeable(new_rule_list.at(i), new_rule_list.at(j));
          // Get the ret2 value, to see the bit position difference and the flag value
          //cout << "i =" << i << " " << "j =" << j << " " << "dif =" << ret2.dif << " " << "flag =" << ret2.flag << endl;
          if (ret2.dif == 0) {
            // the value part is the same on the "0" positions at mask part
            //cout << "Merge rules" << endl;
            newRule7.mask = (new_rule_list.at(i).mask | new_rule_list.at(j).mask);
            newRule7.value = new_rule_list.at(i).value & new_rule_list.at(j).value;
            // The merged rule's priority should equal to the highest priority
            newRule7.priority = min( new_rule_list.at(i).priority, new_rule_list.at(j).priority );
            newRule7.action = new_rule_list.at(i).action;
            //newRule7.priority = new_rule_list.size() - 1;
            //cout << "value = " << newRule7.value << " " << "mask = " << newRule7.mask << " " << "priority = " << newRule7.priority << endl;
            new_rule_list.erase(new_rule_list.begin() + i);
            new_rule_list.erase(new_rule_list.begin() + (j-1));
            // Insert the new merged rule into the beginning of the vector
            new_rule_list.push_back(newRule7);
            i = -1;
            break;
          }
          if (ret2.dif == 1) {
            // There is just one bit position different
            //cout << "Merge rules" << endl;
            newRule7.mask = (new_rule_list.at(i).mask | new_rule_list.at(j).mask)
                + (uint64_t(1) << ret2.flag);
            newRule7.value = new_rule_list.at(i).value & new_rule_list.at(j).value;
            newRule7.priority = min( new_rule_list.at(i).priority, new_rule_list.at(j).priority );
            newRule7.action = new_rule_list.at(i).action;
            //newRule7.priority = new_rule_list.size() - 1;
            //cout << "value = " << newRule7.value << " " << "mask = " << newRule7.mask << " " << "priority = " << newRule7.priority << endl;
            new_rule_list.erase(new_rule_list.begin() + i);
            new_rule_list.erase(new_rule_list.begin() + (j-1));
            // Insert the new merged rule into the beginning of the vector
            new_rule_list.push_back(newRule7);
            i = -1;
            break;
          }
          else {
            continue;
          }
        }
        else {
          continue;
        }
      }
      else {
        continue;
      }
    }
  }
  /*
  for (int k = 0; k < new_rule_list.size(); k++) {
    cout << "value part:" << new_rule_list.at(k).value << " " << "mask part:" <<
            new_rule_list.at(k).mask  << endl;
  }
  */
  return new_rule_list;
}

/*
 * Check whether the new rule is a prefix rule
 * if yes, do the LPM insertion
 * if not, do the expand rule function
*/
bool is_prefix(Rule& rule)
{
  // Store the wildcard postion into vector maskPosion
  vector<uint32_t> maskPosition;
  // Check the mask field from the lower bit
  for(int i = 0; i < 64; i++) {
    // if this: get the position whose bit is 1 (have wildcard)
    if((rule.mask >> i) & uint64_t(1) == 1) {
      maskPosition.push_back(i);
    }
  }
  uint32_t num = maskPosition.size(); // num is the number of wildcard
  if (rule.mask == (uint64_t(1) << num)-1) {
    return true;
  }
  else {
    return false;
  }
}



// Get the number of wildcard * in a rule
// The rule is 64-bit
int get_numOFwildcard(Rule& rule)
{
  int count = 0; // show the number of wildcard
  for(int i = 0; i < 64; i++) {
    // if this: get the position whose bit is 1 (have wildcard)
    if((rule.mask >> i) & uint64_t(1) == 1) {
      count++;
    }
  }
  return count;
}

/*
 * Bit-weaving paper
 * sort the two rules by the number of wildcard
 * call the get_numOFwildcard function
*/
bool bw_wayToSort(Rule a, Rule b)
{
  int num_a = get_numOFwildcard(a);
  int num_b = get_numOFwildcard(b);
  return (num_a < num_b);
}

// Sorting the rules in an asscending order
bool wayToSort(Rule aa, Rule bb)
{
  return (aa.mask < bb.mask);
}

bool wayToSort1(Rule aaa, Rule bbb)
{
  return (aaa.value < bbb.value);
}

/*
 * Bit-weaving paper
 * sort function: according to the number of wildcard in the rules
 * first: get the number of wildcard, put the number into an int vector
 * second: sort this number int vector in an ascending order
*/
vector<Rule> bw_sortrules(vector<Rule>& ruleList)
{
  //vector<Rule> bw_sortTable;
  std::sort(ruleList.begin(), ruleList.end(), bw_wayToSort);
//  for (int k = 0; k < ruleList.size(); k ++) {
//    cout << ruleList[k].value << ", " << ruleList[k].mask << ", "
//         << ruleList[k].priority << ", " << ruleList[k].action << endl;
//  }
  return ruleList;
}

/*
 * Sorting the prefix format rules into asscending order, denpending on the prefix length
 * using the std::sort function
*/
vector<Rule> sort_rules(vector<Rule>& ruleList)
{
  std::sort(ruleList.begin(), ruleList.end(), wayToSort);
  /*
  cout << "mark" << "===============" << endl;
  for (int k = 0; k < ruleList.size(); k ++) {
    cout << ruleList[k].value << ", " << ruleList[k].mask << endl;
  }
  */
  vector<Rule> sortTable;
  vector<Rule> sortTotalTable;
  // Determine the size of combined table
  sortTotalTable.reserve(ruleList.size());
  for (int i = 0; i < ruleList.size(); i ++) {
    if (i != ruleList.size() - 1) {
      if (ruleList.at(i).mask == ruleList.at(i+1).mask) {
        // if the mask value is the same, push into the same vector
        //cout << "test" << endl;
        sortTable.push_back(ruleList.at(i));
        continue;
      }
      else {
        sortTable.push_back(ruleList.at(i));
        //cout << "i = " << i << endl;
        std::sort(sortTable.begin(), sortTable.end(), wayToSort1);
        sortTotalTable.insert( sortTotalTable.end(), sortTable.begin(), sortTable.end() );
        /*
        for (int k = 0; k < sortTotalTable.size(); k ++) {
          cout << sortTotalTable[k].value << ", " << sortTotalTable[k].mask << endl;
        }
        cout << "sortTotalTable size = " << sortTotalTable.size() << endl;
        */
        // Delete the current contents, clear the memory
        sortTable.clear();
        //cout << "sortTable size = " << sortTable.size() << endl;
        continue;
      }
    }
    else {
      // for the last element in the vector
      // for avoiding the over-range of the vector
      if (ruleList.at(i).mask == ruleList.at(i-1).mask) {
        sortTable.push_back(ruleList.at(i));
        //cout << "i = " << i << endl;
        std::sort(sortTable.begin(), sortTable.end(), wayToSort1);
        sortTotalTable.insert( sortTotalTable.end(), sortTable.begin(), sortTable.end() );
      }
      else {
        std::sort(sortTable.begin(), sortTable.end(), wayToSort1);
        sortTotalTable.insert( sortTotalTable.end(), sortTable.begin(), sortTable.end() );
        sortTable.clear();
        sortTable.push_back(ruleList.at(i));
        sortTotalTable.insert( sortTotalTable.end(), sortTable.begin(), sortTable.end() );
      }
    }
  }
  return sortTotalTable;
}

/*
 * Generate the two dimensional array (generate delta array) from the pingRulesTable array
 * With all the bits in each rule, including "0" and "1"
 * Caculate the score--the sum of column
*/
vector<int> generate_delta(vector<Rule>& ruleList)
{
  vector<uint64_t> sumColumn;
  for (int j = 0; j < 64; j++) {
    uint32_t score = 0;
    for (int i = 0; i < ruleList.size(); i++) {
      score += ((((ruleList.at(i)).mask) >> j) & uint64_t(1));
    }
    sumColumn.push_back(score);
  }

  // Copy the sumColumn vector to a new vector
  vector<uint64_t> newSumColumn(sumColumn);
  /*
   * Checked the newSumColumn vector is the same with the sumColumn vector
  cout << newSumColumn.size() << endl;
  for (i = 0; i < newSumColumn.size(); i++) {
    cout << newSumColumn[i] << endl;
  }
  */

  // Sort the newSumColumn vector in descending order
  std::sort(newSumColumn.begin(), newSumColumn.end(), std::greater<uint64_t>());
  /*
   * Checked the descending order is correct or not
  for (i = 0; i < newSumColumn.size(); i++) {
    cout << newSumColumn[i] << endl;
  }
  */

  // Construct the delta(): the rearrangement operation {left shift, right shift, and no change}
  // the element in delta vector, can be negative, positive and "0"
  vector<int> delta;
  // checkpoint is the index/subscript of the newSumColumn has the same value with the sumColumn
  uint32_t checkpoint = 0;
  int gap = 0; // Gap is the difference between the original and new sumcolumn vectors
  for (int i = 0; i < sumColumn.size(); i++) {
    //cout << "mark1" << " " << sumColumn[i] << endl;
    for (int j = 0; j < newSumColumn.size(); j++) {
      //cout << newSumColumn[j] << endl;
      // Check the first equal element, if it is true, then return the checkpoint
      if (newSumColumn[j] != sumColumn[i]) {
        continue;
      }
      else if (newSumColumn[j] == sumColumn[i]) {
        checkpoint = j;
        newSumColumn[j] = 132; // make the matched column invalid
        break;
      }
      else {
        // Search all the 64 values, still didn't find the same value
        cout << "Error occurs" << endl;
      }
    }
    // Get the difference between the original vector data and the sorted vector data
    // Create the rearrangement operation
    gap = i - checkpoint;
    delta.push_back(gap);
  }
  return delta;
}

/*
 * Generate the new rule after the delta operations
 * if the element value of delta vector is negative, which means left shift
 * if the element value of delta vector is positive, which means right shift
 * if the element value of delta vector is "0", which means no change
*/
// Create a new pingRulesTable for the new rearrangement rules
//vector<Rule> newPingRulesTable; // for each bit of each rule
vector<Rule> rules_rearrange(vector<Rule>& oldRuleList, vector<int> delta_array)
{
  vector<Rule> sumRulesTable; // for a new rule

  for (int i = 0; i < oldRuleList.size(); i++) {
    Rule newRule;
    for (int j = 0; j < 64; j++) {
      Rule subRule;
      if (delta_array[j] < 0) {
        // if it is negative, do the left shift
        // from the lsb position, do the correct operations
        // Note: because here is 64 bit, if we just use 1 to do left shift, it will occur overflow
        // since "1" is 32bit by default
        subRule.value = ( (( (oldRuleList[i].value) & (uint64_t(1) << j) ) ) << (abs(delta_array[j])) );
        subRule.mask = ( (( (oldRuleList[i].mask) & (uint64_t(1) << j) ) ) << (abs(delta_array[j])) );
      }
      else if (delta_array[j] > 0) {
        // if it is positive, do the right shift
        subRule.value = ( (( (oldRuleList[i].value) & (uint64_t(1) << j) ) ) >> (abs(delta_array[j])) );
        subRule.mask = ( (( (oldRuleList[i].mask) & (uint64_t(1) << j) ) ) >> (abs(delta_array[j])) );
      }
      else if (delta_array[j] == 0) {
        // if it is "0", no change
        subRule.value = (( (oldRuleList[i].value) & (uint64_t(1) << j) ) );
        subRule.mask = (( (oldRuleList[i].mask) & (uint64_t(1) << j) ) );
      }
      newRule.value |= subRule.value;
      newRule.mask |= subRule.mask;
      //cout << j << " " << newRule.mask << endl;
      newRule.priority = oldRuleList[i].priority;
      newRule.action = oldRuleList[i].action;
    }
    sumRulesTable.push_back(newRule);
  }
  return sumRulesTable;
}

/*
 * Rearrange each key in the keyTable according to the delta vector
 * because the rules are being reordered by the delta vector
*/

uint64_t keys_rearrange(uint64_t key, vector<int> delta_array)
{
  // Calculate the key rearrangement configure time basing on the delta vector

  uint64_t newKey = 0; // new key after reordering
  for (int j = 0; j < 64; j++) {
    uint64_t subKey = 0; // subKey is the single bit value of each key
    if (delta_array[j] < 0) {
      subKey = ( (( key & (uint64_t(1) << j) ) ) << (abs(delta_array[j])) );
    }
    else if (delta_array[j] > 0) {
      // if it is positive, do the right shift
      subKey = ( (( key & (uint64_t(1) << j) ) ) >> (abs(delta_array[j])) );
    }
    else if (delta_array[j] == 0) {
      // if it is "0", no change
      subKey = (( key & (uint64_t(1) << j) ) );
    }
    newKey |= subKey;
  }
  return newKey;
  //cout << newKey << endl;
}

/*
 *Create a function called construct the data structure
 *Insert rules
*/

// function to call if operator new can't allocate enough memory or error arises
void outOfMemHandler()
{
  std::cerr << "Unable to satisfy request for memory\n";

  std::abort();
}



/*
 *Create a function called the whole search process
 *search rules
*/

//static int threshold; // Set the wildcard num as a variable
int main(int argc, char* argv[])
{
  // Input the action file
  vector<int> actions;
  string line1;
  uint32_t action1;
  ifstream file2 (argv[3]);
  char* _eMemory = new char[16384];

  // Read action from the txt file
  if (file2.is_open()) {
    while (!file2.eof()) {
      getline(file2, line1);
      if (!line1.empty()) {
        action1 = stoull(line1);
        actions.push_back(action1);
      }
    }
  }
  file2.close();
  // Set the hard line for the memory cost == number of trie node
  //threshold = stoull(argv[4]);
  ifstream file (argv[1]);
  // Read the rules from txt file
  vector<Rule> oldpingRulesTable;
  int i = 0;
  if (file.is_open()) {
    while (!file.eof()) {
      // Read lines as long as the file is
      string line;
      getline(file,line);
      if(!line.empty()) {
        Rule rule = strTint(line);
        // Add the priority feature when generating rules
        // Priority is in-order of generating
        rule.action = actions[i];
        i = i + 1;
        rule.priority = i;
        //rule.priority = ++i;
        // Push the input file into ruleArray
        oldpingRulesTable.push_back(rule);
      }
    }
  }
  file.close();
  // Need to check the priority preserve the same after sorting
  //vector<Rule> pingRulesTable = sort_rules(oldpingRulesTable);
  vector<Rule> pingRulesTable = bw_sortrules(oldpingRulesTable);
  //cout << "Sorted total size = " << pingRulesTable.size() << endl;
  //vector<Rule> pingRulesTable = merge_rules(oldpingRulesTable);
  //cout << "Merged total size = " << pingRulesTable.size() << endl;
  /*
  for (int k = 0; k < pingRulesTable.size(); k++) {
    cout << pingRulesTable[k].priority << " " << pingRulesTable[k].action << " " << pingRulesTable[k].value << " " << pingRulesTable[k].mask << endl;
  }
  */


  // Read in keys from file:
  ifstream file1 (argv[2]);
  vector<uint64_t> keyTable;
  if (file1.is_open()) {
    while (!file1.eof()) {
      // Read lines as long as the file is
      string packet;
      getline(file1,packet);
      if(!packet.empty()) {
        uint64_t key = stoull(packet);
        // Push the input file into ruleArray
        keyTable.push_back(key);
      }
    }
  }
  file1.close();
  cout << "++++++Group_nolimit algorithm+++++" << endl;
  cout << "The num of keys: " << keyTable.size() << endl;
  cout << "The num of rules: " << pingRulesTable.size() << endl;
  // Genearte the different size of key nums


  /*
   * Grouping algorithm
   * Use the is_cross_pattern function to check the grouping number
   * Avoid the expanding number is too large
   * how to improve the grouping algorithm??
   * add the threshold, to adjust the grouping seperation
  */



  //set the new_handler


  // For the grouped rule table
  vector<uint32_t> groupVector;
  vector<Rule> newList;

  // avoid the bad allocation memory
  // The grouping algorithm is to create the most number of
  // groups without expansion

  /*
   * Noexpand group algorithm
  */

  for ( int i = 0; i < pingRulesTable.size(); i++ ) {
    if (i < (pingRulesTable.size()-1)) {
      newList.push_back(pingRulesTable[i]);
      vector<int> new_generated_delta = generate_delta(newList);
      // Create the rearranged rule set
      vector<Rule> new_table_list = rules_rearrange(
            newList, new_generated_delta );
      for ( int k = 0; k < new_table_list.size(); k++ ) {
        //Trie trie1; // for caculating the trie1.new_num
        // for guarantee avoding the bad memory alloc
        if ( is_prefix(new_table_list.at (k)) ) {
          // if this is prefix rules, don't need to expand
          //trie1.insert_prefix_rule_priority(new_table_list.at(k));
          continue;
        }
        else {
          groupVector.push_back(i-1);
          // clear the newList vector, becasue this is a seperated group
          newList.clear();
          i = i -1;
          break;
        }
      }
    }
    else {
      groupVector.push_back(i);
    }
  }
  //==========================================

  // Copy the groupVector, in order to recover the deleted element later
  vector<uint32_t> original_groupVector(groupVector);
  cout << "(No expand) Num of Original groups is:" << " " << original_groupVector.size() << endl;

  cout << "Num of groups is:" << " " << groupVector.size() << endl;


  vector< vector<Rule> > newbigArray;
  // Create a new sub group by copying the related rules

  for (int m = 0; m < groupVector.size(); m++) {
    newbigArray.push_back(vector<Rule> ());
  }

  for (int j = 0; j < groupVector.size(); j++) {
    if (j == 0) {
      for (int i = 0; i < (groupVector[j] + 1); i++) {
        newbigArray[j].push_back(pingRulesTable.at(i));
      }
      continue;
    }
    else {
      for (int k = (groupVector[j-1] + 1); k < (groupVector[j] + 1); k++) {
        newbigArray[j].push_back(pingRulesTable.at(k));

      }
      continue;
    }
  }

  // Start to build the newRules in each group
  /*
   * We get the new rearrangement rules table here, named sumRulesTabel
   * Next, we will do the rules insertion
   * Here, we just insert prefix rules, follow the LPM insertion function
   * So we need to check whether each new rules is prefix rule
   * If it is, then do the insertion
   * if not, do the expansion algorithm to make it is prefix rule
  */

  int newexpandRule_num = 0;
  int newinsertRule_num = 0;

  uint64_t newsum_trie_expand_count = 0;
  uint64_t newsum_trie_count = 0;
  uint64_t newsum_trie_node_count = 0;
  auto newsum_rule_rearrange_time = 0;
  auto newsum_rule_insertion_time = 0;

  //get time1
  //auto start = get_time::now(); // use auto keyword to minimize typing strokes :)
  // Define a 2D vector for storing delta vector
  vector< vector<int> > newdelta_vector;
  // Allocate an array to hold my class objects
  vector<Trie> newtries(groupVector.size());
  //Trie* trie = new Trie[groupVector.size()];

  // Start to construct the trie data structure here
  for (int j = 0; j < groupVector.size(); j++) {
    // Initilize a trie
    // Each group is a seperate trie
    // Initialize each trie

    auto start1 = get_time::now();

    vector<int> delta_need = generate_delta(newbigArray[j]);
    // Push each delta vector into the 2D vector
    newdelta_vector.push_back(delta_need);
    vector<Rule> newnewnewTable = rules_rearrange(newbigArray[j], delta_need);

    // Sorting the rules in each group into asscending order
    // prepare for the merging next
    //vector<Rule> newnewTable = merge_rules(newSumRuleTable);
    auto end1 = get_time::now();
    auto diff1 = end1 - start1;
    newsum_rule_rearrange_time += chrono::duration_cast<ms>(diff1).count();
    // Doing the rule insertion
    auto start2 = get_time::now();
    for (int k = 0; k < newnewnewTable.size(); k++) {
      if ( is_prefix(newnewnewTable.at(k)) ) {
        newtries[j].insert_prefix_rule_priority(newnewnewTable.at(k));
        newinsertRule_num ++;
      }
      else {
        // becasue we control the number of expanding wildcard
        // so don't need to delete rules manually
        //cout << "group index=" << j << ", index num: " << k << "," << "value: "<< newnewnewTable[k].value << "," << "mask: "
        //<< newnewnewTable[k].mask << endl;
        newtries[j].expand_rule(newnewnewTable.at(k));
        newexpandRule_num ++;
      }
    }
    //cout << "j=" << j << ", " << "count number: " << tries[j].count << endl;
    //cout << "j=" << j << ", " << "trie node num: " << newtries[j].node_count << endl;
    auto end2 = get_time::now();
    auto diff2 = end2 - start2;
    newsum_rule_insertion_time += chrono::duration_cast<ms>(diff2).count();
    newsum_trie_expand_count += newtries[j].expand_count;  // correct
    newsum_trie_count += newtries[j].count;
    newsum_trie_node_count += newtries[j].node_count;

  }



  // Finished the rearranged rule insertion for each subtrie
  // Doing the rule searching
  char output[][32] = {"Not present in rulesTable", "Present in rulesTable"};
  uint64_t actionSum = 0;
  uint64_t checksum = 0; // show the sum of matching priority
  uint64_t match = 0; // how many keys are being matched in these new rules
  auto newsum_key_rearrange_time = 0;
  auto newsum_key_search_time = 0;

  for (int i = 0; i < keyTable.size(); i++) {
    // Check each key
    auto start3 = get_time::now();
    vector<uint64_t> matchVector;
    vector<uint32_t> decisionVector;
    for (int m = 0; m < groupVector.size(); m++) {
      uint64_t newGenKey = keys_rearrange(keyTable[i], newdelta_vector[m]);
      auto end3 = get_time::now();
      auto diff3 = end3 - start3;
      newsum_key_rearrange_time += chrono::duration_cast<ms>(diff3).count();
      auto start4 = get_time::now();
      trie_result search_ret = newtries[m].LPM1_search_rule(newGenKey);
      //uint64_t priority = tries[m].LPM1_search_rule(newGenKey);
      //cout << "Priority value: " << search_ret.priority << ", Action value: " << search_ret.action << endl;
      auto end4 = get_time::now();
      auto diff4 = end4 - start4;
      // Insert all the priority value, including match and no_match
      //matchVector.push_back(priority);
      matchVector.push_back(search_ret.priority); // Store the priority value
      decisionVector.push_back(search_ret.action);
      //cout << "test value: " << search_ret.action << endl; // Has a bug here....... action should not be 0
      // Find the bug, the expand function did not insert the action attribute value
      newsum_key_search_time += chrono::duration_cast<ns>(diff4).count();
    }
    //cout << "matchVector size: " << matchVector.size() << endl;
    //cout << "decisionVector size: " << decisionVector.size() << endl; // should be the same
    vector<uint64_t> test1; // Store the priority value
    vector<uint32_t> test2; // Store the action value
    for (int v = 0; v < matchVector.size(); v++) {
      if (matchVector[v] == 0) {
        continue;
      }
      else {
        uint64_t test = matchVector[v];
        uint32_t action2 = decisionVector[v];
        test1.push_back(test);
        test2.push_back(action2);
        continue;
      }
    }

    // Choose the smallest one, which means the highest priority
    if (test1.size() > 0) {
      uint64_t match_final = *min_element(test1.begin(), test1.end());
      checksum += match_final;
      match++;
      vector<uint64_t>::iterator it;
      it = find(test1.begin(), test1.end(),match_final);
      int position1 = distance(test1.begin(), it);
      //cout << "action size: " << test2.size() << endl;
      /*
      for (int q = 0; q < test2.size(); q++) {
        cout << "action set==="  << q  << " " << test2[q] << endl;
      }
      */
      actionSum += test2.at(position1);
      //cout << "i index:" << j << ", action=:" << decision << endl;
      //cout << "i index:" << i << ", action=" << test2.at(position1) << endl;
      //cout << "i index:" << i << " " << "priority=:" << match_final << ", action=" << test2.at(position1) << endl;
    }

  }

  //get time2
  //auto end = get_time::now();
  //auto diff = end - start;

  cout << "Total rules rearrange configure time is:" << newsum_rule_rearrange_time << endl;
  cout << "Total rules insertion configure time is:" << newsum_rule_insertion_time << endl;
  cout << "Total keys rearrange configure time is:" << newsum_key_rearrange_time << endl;
  cout << "Total keys search time is:" << newsum_key_search_time << endl;
  cout << "Total expanded count is:" << " " << newsum_trie_expand_count << endl;
  cout << "Expand rule num is:" << " " << newexpandRule_num << endl;
  cout << "Insert rule num is:" << " " << newinsertRule_num << endl;
  cout << "Total insert rule num is:" << " " << newsum_trie_count << endl;
  cout << "Total insert trie_node count is:" << " " << newsum_trie_node_count << endl;
  cout << "Checksum: " << checksum << endl;
  cout << "ActionSum: " << actionSum << endl;
  cout << "Total matches: " << match << endl;
  cout << "==================================================" << endl;




  return 0;
}





