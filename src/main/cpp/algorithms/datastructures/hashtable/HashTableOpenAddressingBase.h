/*
 * @file   HashTableOpenAddressingBase.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   An implementation of base class for hashtables.
 * Base class for hashtables with an open addressing collision resolution method such as linear
 * probing, quadratic probing and double hashing.
 */

#ifndef D_HASHTABLEOPENADDRESSING_H
#define D_HASHTABLEOPENADDRESSING_H

#include <vector>
#include <deque>
#include <list>
#include <set>   // set and multiset
#include <map>   // map and multimap
#include <unordered_set>  // unordered set/multiset
#include <unordered_map>  // unordered map/multimap
#include <iterator>
#include <algorithm>
#include <numeric>    // some numeric algorithm
#include <functional>
#include <stack>

#include <sstream>
#include <memory>
#include <iostream>
#include <cmath>

namespace dsa {

static const int DEFAULT_CAPACITY = 7;
static const double DEFAULT_LOAD_FACTOR = 0.65;

template <class KEY, class VALUE>
class HashTableOpenAddressingBase {

protected:
  // This is the linear constant used in the linear probing, it can be
  // any positive number. The table capacity will be adjusted so that
  // the GCD(capacity, LINEAR_CONSTANT) = 1 so that all buckets can be probed.
 const int LINEAR_CONSTANT = 17;

  double loadFactor_;
  int capacity_, threshold_, modificationCount_;

  // 'usedBuckets' counts the total number of used buckets inside the
  // hash-table (includes cells marked as deleted). While 'keyCount'
  // tracks the number of unique keys currently inside the hash-table.
  int usedBuckets_, keyCount_;

  // These arrays store the key-value pairs.
  std::vector<int> usedKeys_;
  std::vector<KEY> keys_;
  std::vector<VALUE> values_;

  // Special marker token used to indicate the deletion of a key-value pair
  const int TOMBSTONE = -1;


public:
  HashTableOpenAddressingBase() : HashTableOpenAddressingBase(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR) {
  }

  HashTableOpenAddressingBase(int capacity) : HashTableOpenAddressingBase(capacity, DEFAULT_LOAD_FACTOR) {
  }

  // Designated constructor
  HashTableOpenAddressingBase(int capacity, double loadFactor) {
    if (capacity <= 0) throw std::invalid_argument("Illegal capacity: " + std::to_string(capacity));

    if (loadFactor <= 0 || std::isnan(loadFactor) || std::isinf(loadFactor)){
      throw std::invalid_argument("Illegal loadFactor: " + std::to_string(loadFactor));
    }

    loadFactor_ = loadFactor;
    capacity_ = std::max(DEFAULT_CAPACITY, capacity);
    adjustCapacity();
    threshold_ = (int) (capacity_ * loadFactor);

    usedKeys_ = std::vector<int>(capacity_, 0);
    keys_ = std::vector<KEY>(capacity_);
    values_ = std::vector<VALUE>(capacity_);

    usedBuckets_ = 0;
    keyCount_ = 0;
    modificationCount_ = 0;
  }

  virtual ~HashTableOpenAddressingBase() {
    usedKeys_.clear();
	keys_.clear();
	values_.clear();
  }

protected:
  // These three methods are used to dictate how the probing is to actually
  // occur for whatever open addressing scheme you are implementing.
  virtual void setupProbing(const KEY &key) { }

  virtual int probe(int x) {
    return LINEAR_CONSTANT * x;
  }

  // Adjusts the capacity of the hash table after it's been made larger.
  // This is important to be able to override because the size of the hashtable
  // controls the functionality of the probing function.
  virtual void adjustCapacity() {
    while (gcd(LINEAR_CONSTANT, capacity_) != 1) {
      capacity_++;
    }
  }

  // Increases the capacity of the hash table.
  void increaseCapacity() {
    capacity_ = (2 * capacity_) + 1;
  }

public:
  void clear() {
    std::fill(usedKeys_.begin(), usedKeys_.end(), 0);
    keyCount_ = usedBuckets_ = 0;
    modificationCount_++;
  }

  // Returns the number of keys currently inside the hash-table
  int size() const {
    return keyCount_;
  }

  // Returns the capacity of the hashtable (used mostly for testing)
  int getCapacity() const {
    return capacity_;
  }

  // Returns true/false depending on whether the hash-table is empty
  bool isEmpty() const {
    return keyCount_ == 0;
  }

  void put(const KEY &key, const VALUE &value) {
    insert(key, value);
  }

  void add(const KEY &key, const VALUE &value) {
    insert(key, value);
  }

  bool del(const KEY &key) {
    return remove(key);
  }

  // Returns true/false on whether a given key exists within the hash-table.
  bool containsKey(const KEY &key) {
    return hasKey(key);
  }

  // Returns a list of keys found in the hash table
  std::vector<KEY> keys() const {
    std::vector<KEY> hashtableKeys;
    for (int i = 0; i < capacity_; i++)
      if (usedKeys_[i] != 0 && usedKeys_[i] != TOMBSTONE) hashtableKeys.push_back(keys_[i]);
    return hashtableKeys;
  }

  // Returns a list of non-unique values found in the hash table
  std::vector<VALUE> values() const {
	std::vector<VALUE> hashtableValues;
    for (int i = 0; i < capacity_; i++)
      if (usedKeys_[i] != 0 && usedKeys_[i] != TOMBSTONE) hashtableValues.push_back(values_[i]);
    return hashtableValues;
  }

  void print() const {
	std::cout << "[ ";
    for(unsigned i=0;i<usedKeys_.size();i++) { std::cout << "{" << usedKeys_[i] << "," << keys_[i] << "," << values_[i] << "},"; }
    std::cout << " ]";
  }


  // Double the size of the hash-table
protected:
  void resizeTable() {
    increaseCapacity();
    adjustCapacity();

    threshold_ = (int) (capacity_ * loadFactor_);

    usedKeys_.resize(capacity_, 0);
    keys_.resize(capacity_);
    values_.resize(capacity_);

    std::vector<int> oldUsedKeyTable;
    copy(usedKeys_.begin(), usedKeys_.end(), std::back_inserter(oldUsedKeyTable));
    std::vector<KEY> oldKeyTable;
    copy(keys_.begin(), keys_.end(), std::back_inserter(oldKeyTable));
    std::vector<VALUE> oldValueTable;
    copy(values_.begin(), values_.end(), std::back_inserter(oldValueTable));

    clear();

    for (unsigned i = 0; i < oldUsedKeyTable.size(); i++) {
      if (oldUsedKeyTable[i] != 0) {
        if (oldUsedKeyTable[i] != TOMBSTONE) {
          insert(oldKeyTable[i], oldValueTable[i]);
        }
      }
    }

    oldUsedKeyTable.clear();
  }

  // Converts a hash value to an index. Essentially, this strips the
  // negative sign and places the hash value in the domain [0, capacity)
  int normalizeIndex(std::size_t keyHash) const {
    return (keyHash & 0x7FFFFFFF) % capacity_;
  }


public:
  // Finds the greatest common denominator of a and b.
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  // Place a key-value pair into the hash-table. If the value already
  // exists inside the hash-table then the value is updated.
public:
  void insert(const KEY &key, const VALUE &val) {
    if (usedBuckets_ >= threshold_) resizeTable();
    int offset = normalizeIndex(std::hash<KEY>{}(key));

    for (int i = offset, j = -1, x = 1; ; i = normalizeIndex(offset + probe(x++))) {

      if (usedKeys_[i] != 0) {

        // The current slot was previously deleted
        if (usedKeys_[i] == TOMBSTONE) {
          if (j == -1) j = i;

        // The current cell already contains a key
        } else {
          // The key we're trying to insert already exists in the hash-table,
          // so update its value with the most recent value
          if (keys_[i] == key) {

            if (j == -1) {
              values_[i] = val;
            } else {
              usedKeys_[i] = TOMBSTONE;
              usedKeys_[j] = 1;
              keys_[j] = key;
              values_[j] = val;
            }
            modificationCount_++;
            return;
          }

          // Current cell is null so an insertion/update can occur
        }
      } else {
        // No previously encountered deleted buckets
        if (j == -1) {
          usedBuckets_++;
          keyCount_++;
          usedKeys_[i] = 1;
          keys_[i] = key;
          values_[i] = val;

          // Previously seen deleted bucket. Instead of inserting
          // the new element at i where the null element is insert
          // it where the deleted token was found.
        } else {
          keyCount_++;
          usedKeys_[j] = 1;
          keys_[j] = key;
          values_[j] = val;
        }

        modificationCount_++;
        return;
      }
    }
  }

  // Returns true/false on whether a given key exists within the hash-table
  bool hasKey(const KEY &key) {

    int offset = normalizeIndex(std::hash<KEY>{}(key));

    // Start at the original hash value and probe until we find a spot where our key
    // is or hit a null element in which case our element does not exist.
    for (int i = offset, j = -1, x = 1; ; i = normalizeIndex(offset + probe(x++))) {

      if (usedKeys_[i] != 0) {
        // Ignore deleted cells, but record where the first index
        // of a deleted cell is found to perform lazy relocation later.
        if (usedKeys_[i] == TOMBSTONE) {

          if (j == -1) j = i;

          // We hit a non-null key, perhaps it's the one we're looking for.
        } else {

          // The key we want is in the hash-table!
          if (keys_[i] == key) {

            // If j != -1 this means we previously encountered a deleted cell.
            // We can perform an optimization by swapping the entries in cells
            // i and j so that the next time we search for this key it will be
            // found faster. This is called lazy deletion/relocation.
            if (j != -1) {
              // Swap the key-value pairs of positions i and j.
              keys_[j] = keys_[i];
              values_[j] = values_[i];
              usedKeys_[i] = TOMBSTONE;
              usedKeys_[j] = 1;
            }
            return true;
          }

          // Key was not found in the hash-table :/
        }
      }
      else return false;
    }
    return false;
  }

  // Get the value associated with the input key.
  // NOTE: returns null if the value is null AND also returns
  // null if the key does not exists.
  VALUE get(const KEY &key) {
    VALUE val;
    int offset = normalizeIndex(std::hash<KEY>{}(key));

    // Start at the original hash value and probe until we find a spot where our key
    // is or we hit a null element in which case our element does not exist.
    for (int i = offset, j = -1, x = 1; ; i = normalizeIndex(offset + probe(x++))) {

      if (usedKeys_[i] != 0) {
        // Ignore deleted cells, but record where the first index
        // of a deleted cell is found to perform lazy relocation later.
        if (usedKeys_[i] == TOMBSTONE) {

          if (j == -1) j = i;

        // We hit a non-null key, perhaps it's the one we're looking for.
        } else {

          // The key we want is in the hash-table!
          if (keys_[i] == key) {

            // If j != -1 this means we previously encountered a deleted cell.
            // We can perform an optimization by swapping the entries in cells
            // i and j so that the next time we search for this key it will be
            // found faster. This is called lazy deletion/relocation.
            if (j != -1) {
              // Swap key-values pairs at indexes i and j.
              keys_[j] = keys_[i];
              values_[j] = values_[i];
              usedKeys_[i] = TOMBSTONE;
              usedKeys_[j] = 1;
              val = values_[j];
              break;
            } else {
              val = values_[i];
              break;
            }
          }

          // Element was not found in the hash-table :/
        }
      } else break;
    }
    return val;
  }

  // Removes a key from the map and returns the value.
  // NOTE: returns null if the value is null AND also returns
  // null if the key does not exists.
  bool remove(const KEY &key) {

    int offset = normalizeIndex(std::hash<KEY>{}(key));

    // Starting at the original hash probe until we find a spot where our key is
    // or we hit a null element in which case our element does not exist.s
    for (int i = offset, x = 1; ; i = normalizeIndex(offset + probe(x++))) {
      // Key was not found in hash-table.
      if (usedKeys_[i] == 0) {
    	  return false;}

      // Ignore deleted cells
      if (usedKeys_[i] == TOMBSTONE) {
    	  continue;}

      // The key we want to remove is in the hash-table!
      if (keys_[i] == key) {
        keyCount_--;
        modificationCount_++;
        usedKeys_[i] = TOMBSTONE;

        return true;
      }
    }
    return false;
  }


public:
  // Iterator class can be used to sequentially access nodes of queue
  class Iterator
  {
  public:

    // Before the iteration begins record the number of modifications
    // done to the hash-table. This value should not change as we iterate
    // otherwise a concurrent modification has occurred :0
    Iterator(HashTableOpenAddressingBase* parent, int index, int keyCount, int modificationCount) noexcept :
	  parent_(parent),
	  index_(index),
	  keysLeft_(keyCount),
	  MODIFICATION_COUNT_(modificationCount) {
      if (keysLeft_ != 0) {
        while (parent_->usedKeys_[index_] == 0 || parent_->usedKeys_[index_] == parent_->TOMBSTONE) index_++;
        keysLeft_--;
      }
    }

    Iterator& operator=(int idx) {
      this->index_ = idx;
      return *this;
    }

    // Prefix ++ overload
    Iterator& operator++() {
      // The contents of the table have been altered
      if (MODIFICATION_COUNT_ != parent_->modificationCount_) throw std::runtime_error("Concurrent Modification Exception");
      if (keysLeft_ != 0) {
        while (parent_->usedKeys_[index_] == 0 || parent_->usedKeys_[index_] == parent_->TOMBSTONE) index_++;
        keysLeft_--;
      }
      return *this;
    }

    // Postfix ++ overload
    Iterator operator++(int) {
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }

    bool operator!=(const Iterator& iterator) {
      return keysLeft_ != iterator.keysLeft_;
    }

    KEY operator*() {
      return parent_->keys_[index_];
    }

  private:

    HashTableOpenAddressingBase* parent_;
    int index_;
	int keysLeft_;
    int MODIFICATION_COUNT_;
  };


  // Root of LinkedList wrapped in Iterator type
  Iterator begin() {
    return Iterator(this, 0, keyCount_, modificationCount_);
  }

  // End of LInkedList wrapped in Iterator type
  Iterator end() {
    return Iterator(this, 0, 0, modificationCount_);
  }


  // Return a String view of this hash-table.
  std::string toString() const {
	std::stringstream os;
    os << "[ ";
    for (unsigned i = 0; i < usedKeys_.size(); i++)
      if (usedKeys_[i] != 0 && usedKeys_[i] != TOMBSTONE) os << "{" << keys_[i] << "," << values_[i] << "},";
    os << " ]";
    return os.str();
  }


  friend std::ostream& operator<<(std::ostream &strm, const HashTableOpenAddressingBase<KEY,VALUE> &ht) {
    return strm << ht.toString();
  }

};

} // namespace dsa

#endif /* D_HASHTABLEOPENADDRESSING_H */

