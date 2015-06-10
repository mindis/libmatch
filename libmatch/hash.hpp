// Copyright (c) 2015 Flowgrammable.org
// All rights reserved

#ifndef LIBMATCH_HASH_HPP
#define LIBMATCH_HASH_HPP

// The hashing module...
//
// TODO: Actually document the hash table.

#include <vector>
#include <iterator>
#include <boost/optional.hpp>

namespace hash_table
{
static size_t const primes[] = {
          53,        97,       193,       389,       769,
        1543,      3079,      6151,     12289,     24593, 
       49157,     98317,    196613,    393241,    786433, 
     1572869,   3145739,   6291469,  12582917,  25165843,
    50331653, 100663319, 201326611, 402653189, 805306457,
  1610612741,
};
static size_t const nprimes = sizeof(primes) / sizeof(size_t);

namespace data_store
{

// A basic entry type comprised of a key and a value.
template<typename K, typename V>
struct entry
{
  entry()
    : key(), val()
  { }
  
  entry(K const& k, V const& v)
    : key(k), val(v)
  { }

  K key;
  V val;
};


// A linked list entry.
template<typename K, typename V>
struct list_entry : entry<K, V>
{
  list_entry()
    : entry<K, V>(), next(nullptr)
  { }

  list_entry(K const& k, V const& v)
    : entry<K, V>(k, v), next(nullptr)
  { }

  ~list_entry()
  {
    if (nullptr != next)
      delete next;
  }

  list_entry<K, V>* next;
};


// A tree node entry.
template<typename K, typename V>
struct tree_entry : entry<K, V>
{
  tree_entry()
    : entry<K, V>(), left(nullptr), right(nullptr)
  { }

  tree_entry(K const& k, V const& v)
    : entry<K, V>(k, v), left(nullptr), right(nullptr)
  { }

  tree_entry<K, V>* left;
  tree_entry<K, V>* right;
};


// A basic hash table bucket containing a single entry. This
// class is similar to a standard container.
//
// TODO: Define iterators so that this works like a regular
// container.
template<typename T>
class basic_bucket
{ 
public:

  class iterator
  {
    using data_type = basic_bucket<T>*;
    using reference_type = boost::optional<T>&;
    using pointer_type = boost::optional<T>*;
  public:
    // Constructor/Destructor
    iterator(data_type);
    ~iterator();

    // Assignment and Relational operators.
    iterator& operator=(iterator const&);
    bool operator==(iterator const&) const;
    bool operator!=(iterator const&);

    // Prefix increment
    iterator& operator++();
    // Postfix increment
    iterator& operator++(int);

    // Dereferencing operations
    reference_type operator*();
    pointer_type operator->();

  private:
    data_type data_;
  };


  basic_bucket()
  { }

  basic_bucket(T const& v)
    : data_(v)
  { }

  basic_bucket(T& v)
    : data_(std::move(v))
  { }

  // Accessors
  bool is_full() const;
  bool is_empty() const;

  iterator begin();
  iterator end();
  
  T&       get();
  T const& get() const;

  // Mutators
  iterator& insert(T const&);
  iterator& insert(T&&);

  template<typename... Args> 
  iterator& emplace(Args&&...);
  
  void erase(T const&);
  void clear();

private:
  boost::optional<T> data_;
};


// Constructor
template<typename T>
basic_bucket<T>::iterator::iterator(data_type data = 0)
  : data_(data)
{ }


// Destructor
template<typename T>
basic_bucket<T>::iterator::~iterator()
{
  delete data_;
}


// Assignment operator.
template<typename T>
auto
basic_bucket<T>::iterator::operator=(iterator const& other) -> iterator&
{
  data_ = other.data_;
  return *this;
}


// Equality operator
template<typename T>
inline bool 
basic_bucket<T>::iterator::operator==(iterator const& other) const
{
  return (data_ == other.data_);
}


// Inequality operator
template<typename T>
inline bool 
basic_bucket<T>::iterator::operator!=(iterator const& other)
{
  return !(data_ == other.data_);
}


// Prefix increment.
template<typename T>
auto
basic_bucket<T>::iterator::operator++() -> iterator& 
{
  data_++;
  return *this;
}


// Postfix increment.
template<typename T>
auto
basic_bucket<T>::iterator::operator++(int) -> iterator&
{
  iterator temp = *this;
  data_++;
  return *temp;
}


// Dereferencing operator.
template<typename T>
auto
basic_bucket<T>::iterator::operator*() -> reference_type
{
  return *data_;
}


// Dereferencing operator.
template<typename T>
auto
basic_bucket<T>::iterator::operator->() -> pointer_type
{
  return data_;
}


// Retrieves the current value from the bucket. The bucket
// shall not be full.
template<typename T>
inline T&
basic_bucket<T>::get()
{
  assert(!is_empty());
  return *data_;
}


// Retrieves the current value from the bucket. The bucket
// shall not be full.
template<typename T>
inline T const&
basic_bucket<T>::get() const
{
  assert(!is_empty());
  return *data_;
}


// Returns true if the bucket contains a value.
template<typename T>
inline bool 
basic_bucket<T>::is_full() const
{ 
  return (bool)data_; 
}


// Returns true if the bucket does not contain a value.
template<typename T>
inline bool 
basic_bucket<T>::is_empty() const
{ 
  return (bool)data_; 
}


// Copies `t` to the bucket. The bucket shall not be full.
template<typename T>
inline auto 
basic_bucket<T>::insert(T const& t) -> iterator&
{
  assert(is_empty());
  data_ = t;
  return iterator(this);
}


// Moves `t` into the bucket. The bucket shall not be full.
template<typename T>
inline auto 
basic_bucket<T>::insert(T&& t) -> iterator&
{
  assert(is_empty());
  data_ = std::move(t);
  return iterator(this);
}


// Emplace a value with the given `args` into the bucket.
// The bucket shall not be full.
template<typename T>
template<typename... Args>
inline auto
basic_bucket<T>::emplace(Args&&... args) -> iterator&
{
  data_.emplace(std::forward<Args>(args)...);
  return iterator(this);
}


// Erase the value `t` from the bucket. If `t` is not in
// the bucket, no operation is performed.
template<typename T>
inline void 
basic_bucket<T>::erase(T const& t)
{
  if (data_ == t)
    data_ = boost::none;
}


// Clears the bucket of its current value.
template<typename T>
inline void 
basic_bucket<T>::clear()
{
  data_ = boost::none;
}


// Creates an iterator pointing to the bucket.
template<typename T>
inline auto
basic_bucket<T>::begin() -> iterator
{
  return iterator(this);
}


// Creates an iterator pointing past the bucket.
template<typename T>
inline auto
basic_bucket<T>::end() -> iterator
{
  return iterator();
}


// A chained hash table bucket containing chained entries.
template<typename T>
class list_bucket 
{
public:
  list_bucket();
  list_bucket(T const& v);
  ~list_bucket();

  // Accessors

  
  // Retrieves the entry from the bucket.
  boost::optional<T> open();

  
  // Checks if the bucket contains any entries.
  inline bool is_empty();
  
  
  // Mutators

  
  // Adds an entry to the bucket. Since this is an unbounded data store
  // type there is no concept of being 'full'.
  void fill(T const& v);


  // Clears the bucket of its values.
  void
  dump();

private:
  // Data Members
  boost::optional<T> data_;
};


// An array based hash table bucket.
template<typename T>
struct array_bucket
{
  
  array_bucket()
    : array_bucket(10)
  { }

  array_bucket(int n)
    : size(0), capacity(n)
  { 
    data_ = new boost::optional<T>[n];
  }

  ~array_bucket()
  {
    delete data_;
  }


  // Accesors


  // Retrieves the entries from the bucket.
  boost::optional<T>*
  open()
  {
    return (is_empty() ? boost::none : data_);
  }


  // Checks if the bucket is at maximum capacity.
  inline bool
  is_full()
  {
    return size == capacity - 1;
  }


  // Checks if the bucket contains any entries.
  inline bool
  is_empty()
  {
    return size;
  }


  // Mutators


  // Adds an entry if the bucket is not full. Since this is a bounded
  // data store type there is a maximum number of entries that can be
  // held.
  void
  fill(T const& v)
  {
    if (size + 1 < capacity) {
      data_[size++].emplace(v);
    }
  }


  // Clears the bucket of its entries.
  void
  dump()
  {
    delete data_;
    data_ = new boost::optional<T>[capacity];
    size = 0;
  }


  // Data Members
  boost::optional<T>* data_;  // Data store
  int size;                   // Current size
  int capacity;               // Maximum size
};


// A tree based hash table bucket.
// TODO: implement this using an array, not pointers
template<typename T>
struct tree_bucket
{ 
  tree_bucket()
  { }

  tree_bucket(T const& v)
  { 
    data_.emplace(v);
  }

  ~tree_bucket()
  {
    // TODO: Same issue as dump().
    data_ = boost::none;
  }


  // Accessors


  // Retrieves the entries from the bucket.
  boost::optional<T>
  open()
  {
    return (is_empty() ? boost::none : *data_);
  }


  // Checks if the bucket contains any entries.
  inline bool
  is_empty()
  {
    return data_ == boost::none;
  }
  

  // Mutators


  // Adds an entry to the bucket.
  void
  fill(T const& v)
  {
    // TODO: balance & sort the tree when adding to it
    data_.emplace(v);
  }

  
  // Clears the bucket of any entries.
  void
  dump()
  {
    // TODO: Same issue that list_bucket has. Will need to traverse
    // the tree and delete nodes.
    data_ = boost::none;
  }


  // Data Members
  boost::optional<T> data_;
};


} // end namespace data_store


// Encapsulates the open addressing hash table family.
namespace open
{

// A hash table with open addressing and linear probing for
// resolving collisions.
template<typename K, typename V, typename H, typename C>
class linear
{
public:
  using store_type = std::vector<data_store::basic_bucket<data_store::entry<K, V>>>;
  using value_type = data_store::basic_bucket<data_store::entry<K, V>>;
  using hasher = H;
  using compare = C;  

  linear();
  linear(int);
  linear(int, hasher, compare); 

  // Observers
  int size() const { return size_; }
  int buckets() const { return buckets_; }
  bool empty() const { return size_ == 0; }

  // Lookup
  value_type const* find(K const&) const;

  // Mutators
  value_type* insert(K const&, V const&);
  void erase(K const&);

private:
  int get_hash_index(K const&) const;
  int get_entry_index(K const&) const;
  
  // Resizes the hash table when the load reaches a particular value.
  void resize();

private:
  int        size_;    // Current number of entries
  int        buckets_; // Number of buckets
  hasher     hash_;    // Hash function
  compare    cmp_;     // Equality comparison
  store_type data_;    // Data store
};


template<typename K, typename V, typename H, typename C> 
linear<K, V, H, C>::linear()
  : linear(17)
{ }


template<typename K, typename V, typename H, typename C> 
linear<K, V, H, C>::linear(int n)
  : linear(n, hasher(), compare())
{ }


template<typename K, typename V, typename H, typename C> 
linear<K, V, H, C>::linear(int n, hasher h, compare c)
  : size_(0), buckets_(n), hash_(h), cmp_(c), data_(n)
{ }


// Retrieves a key-value pair from the data store.
template<typename K, typename V, typename H, typename C> 
auto
linear<K, V, H, C>::find(K const& key) const -> value_type const*
{
  int idx = get_entry_index(key);    
  if (idx < 0)
    return nullptr;
  return &data_[idx];
}


// Inserts a new key-value pair into an empty bucket.
template<typename K, typename V, typename H, typename C> 
auto
linear<K, V, H, C>::insert(K const& key, V const& value) -> value_type*
{
  int idx = get_hash_index(key);
  while (data_[idx].is_full())
    idx = (idx + 1 < buckets ? idx + 1 : 0);
  data_[idx].insert(data_store::entry<K, V>(key, value));
  ++size;
  return &data_[idx];
}


// Clears the bucket containing the same key, if found.
template<typename K, typename V, typename H, typename C> 
void
linear<K, V, H, C>::erase(K const& key)
{
  int idx = get_entry_index(key);
  if (idx >= 0) {
    data_[idx].clear();
    --size;        
  }
}


// Returns the index in the table for the given key or -1 if not found. 
// This is guaranteed to be the actual index in the table for the key.
template<typename K, typename V, typename H, typename C> 
int
linear<K, V, H, C>::get_entry_index(K const& key) const
{
  int idx = get_hash_index(key); 
  while (!cmp_(data_[idx], key))
    idx = (idx + 1 < buckets ? idx + 1 : 0);
  return (cmp_(data_[idx], key) ? idx : -1);
}


// Returns an index in the table for a given key. This is not guaranteed
// to be the actual index for the key.
template<typename K, typename V, typename H, typename C> 
inline int
linear<K, V, H, C>::get_hash_index(K const& key) const
{ 
  return hash(key) % buckets; 
}


} //end namespace open


namespace closed
{

} // end namespace closed

} // end namespace hash_table

#endif