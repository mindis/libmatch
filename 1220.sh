#!/bin/bash
echo "=====207,S====="
#./optimized_libmatch/test/group_nolimit.test ~/libmatch/test/Benchmarks/207.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt >> result_try1.txt
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/207.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/207.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/207.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt 2000000 >> result_try1.txt
#./optimized_libmatch/test/basic_trie_group.test ~/libmatch/test/Benchmarks/207.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt >> result_try1.txt

echo "=====207_1====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/207_1.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/207_1.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt 2000000 >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/207_1.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt >> result_try1.txt

echo "=====207 original====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/ping_big_reduced_64bit_24_32_src_32des.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/ping_big_reduced_64bit_24_32_src_32des.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt 2000000 >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/ping_big_reduced_64bit_24_32_src_32des.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt >> result_try1.txt

echo "=====461====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/461.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/461.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt 2000000 >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/461.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt >> result_try1.txt

echo "=====461_1====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/461_1.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/461_1.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt 2000000 >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/461_1.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt >> result_try1.txt

echo "=====461 original====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/newRule_noexpand_461.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/newRule_noexpand_461.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt 2000000 >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/newRule_noexpand_461.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt >> result_try1.txt

#./optimized_libmatch/test/group_search_reviewed.test ~/libmatch/test/Benchmarks/newRule_less12_553.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action553.txt >> result_try1.txt
#./optimized_libmatch/test/linear_arbitrary.test ~/libmatch/test/Benchmarks/newRule_less12_553.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action553.txt >> result_try1.txt
#./optimized_libmatch/test/basic_trie_group.test ~/libmatch/test/Benchmarks/newRule_less12_553.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action553.txt >> result_try1.txt

echo "=====553====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/newRule_less12_553.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action553.txt >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/newRule_less12_553.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action553.txt >> result_try1.txt

echo "=====605====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/ping_small_64bit.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action605.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/ping_small_64bit.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action605.txt 2000000 >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/ping_small_64bit.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action605.txt >> result_try1.txt

echo "====1683====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/1683.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1683.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/1683.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1683.txt 2000000 >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/1683.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1683.txt >> result_try1.txt

#./optimized_libmatch/test/group_search_reviewed.test ~/libmatch/test/Benchmarks/newRule_noexpand_1683.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1683.txt >> result_try1.txt
#./optimized_libmatch/test/linear_arbitrary.test ~/libmatch/test/Benchmarks/newRule_noexpand_1683.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1683.txt >> result_try1.txt
#./optimized_libmatch/test/basic_trie_group.test ~/libmatch/test/Benchmarks/newRule_noexpand_1683.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1683.txt >> result_try1.txt
echo "====1911====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/newRule_less12_1911.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1911.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/newRule_less12_1911.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1911.txt 2000000 >> result_try1.txt
./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/newRule_less12_1911.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1911.txt >> result_try1.txt

echo "====2925====="
./optimized_libmatch/test/bw_noexpand_sort.test ~/libmatch/test/Benchmarks/ping_big_64bit_original.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action2925.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/ping_big_64bit_original.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action2925.txt 2000000 >> result_try1.txt



./optimized_libmatch/test/group_noexpand_base.test ~/libmatch/test/Benchmarks/ping_big_64bit_original.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action2925.txt >> result_try1.txt
#./optimized_libmatch/test/group_advanced.test ~/libmatch/test/Benchmarks/ping_big_64bit_original.txt ~/libmatch/test/Benchmarks/two_fields_64bit_big.txt ~/libmatch/test/Benchmarks/action2925.txt >> result_try1.txt
#./optimized_libmatch/test/basic_trie_group.test ~/libmatch/test/Benchmarks/ping_big_64bit_original.txt ~/libmatch/test/Benchmarks/two_fields_64bit_big.txt ~/libmatch/test/Benchmarks/action2925.txt >> result_try1.txt

./optimized_libmatch/test/ping_noexpand.test ~/libmatch/test/Benchmarks/207.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action207.txt
./optimized_libmatch/test/ping_noexpand.test ~/libmatch/test/Benchmarks/461.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action461.txt
./optimized_libmatch/test/ping_noexpand.test ~/libmatch/test/Benchmarks/newRule_less12_553.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action553.txt >> result_try1.txt
./optimized_libmatch/test/ping_noexpand.test ~/libmatch/test/Benchmarks/ping_small_64bit.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action605.txt
./optimized_libmatch/test/ping_noexpand.test ~/libmatch/test/Benchmarks/1683.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1683.txt
./optimized_libmatch/test/ping_noexpand.test ~/libmatch/test/Benchmarks/newRule_less12_1911.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action1911.txt
./optimized_libmatch/test/ping_noexpand.test ~/libmatch/test/Benchmarks/ping_big_64bit_original.txt ~/libmatch/test/Benchmarks/two_fields_64bit.txt ~/libmatch/test/Benchmarks/action2925.txt
