/*
 * @file   HashTableLinearProbingTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   17 July 2020
 * @version 0.1
 * @brief   A hash table unit test.
 */

#include <gtest\gtest.h>
#include <HashTableLinearProbing.h>

#include <chrono>
#include <random>
#include <list>
#include<iterator>
#include<vector>
#include <algorithm>

namespace dsa {

namespace hashtabletest {

static int LOOPS = 500;

static double randDouble(double start_in, double end_in)
{
  double f = (double)rand() / RAND_MAX;
  return start_in + f * (end_in - start_in);
}


static int randInt(int start_in, int end_in)
{
//  srand((unsigned) time(0));
  int randomNumber = rand()*(end_in - start_in)/RAND_MAX + start_in;
  return randomNumber;
}


static std::vector<int> genRandList(int start_in, int end_in, int num_in)
{
  std::vector<int> randvec;
  auto containsNum = [&randvec](int a) -> bool { auto iter = std::find(randvec.begin(), randvec.end(), a); return iter != randvec.end(); };
  for(int i=0; i < num_in; ++i) {
    int rndVal;
    do {
      rndVal = randInt(start_in, end_in);
//      std::cout << "start:" << start_in << " end:" << end_in << " rnd:" << rndVal << " rpt:" << containsNum(rndVal) << std::endl;
    } while (containsNum(rndVal));
    randvec.push_back(rndVal);
  }
  std::random_shuffle(randvec.begin(), randvec.end());
  return randvec;
}


std::vector<int> extract_keys(std::multimap<int, int> const& input_map) {
  std::vector<int> retval;
  for (auto const& element : input_map) {
    retval.push_back(element.first);
  }
  return retval;
}



TEST(HashTableLinearProbingTest, testIllegalCreation1) {
  try {
    HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>(-3, 0.5);
  }
  catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Illegal capacity: -3"));
  }
  catch(...) {
    FAIL() << "Expected std::invalid_argument Illegal capacity: -3";
  }
}


TEST(HashTableLinearProbingTest, testIllegalCreation2) {
  try {
    HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>(5, std::numeric_limits<double>::infinity());
  }
  catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Illegal loadFactor: inf"));
  }
  catch(...) {
    FAIL() << "Expected std::invalid_argument Illegal loadFactor: inf";
  }
}


TEST(HashTableLinearProbingTest, testIllegalCreation3) {
  try {
    HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>(6, -0.5);
  }
  catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Illegal loadFactor: -0.500000"));
  }
  catch(...) {
    FAIL() << "Expected std::invalid_argument Illegal loadFactor: -0.500000";
  }
}


#if 1
TEST(HashTableLinearProbingTest, testUpdatingValue) {
  HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>();

  map.add(1, 1);
  ASSERT_EQ(1, map.get(1));

  map.add(1, 5);
  ASSERT_EQ(5, map.get(1));

  map.add(1, -7);
  ASSERT_EQ(-7, map.get(1));

  map.add(8294, 8294);
  ASSERT_EQ(8294, map.get(8294));

}


TEST(HashTableLinearProbingTest, testIterator) {

  HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>();
  std::unordered_map<int, int> stdMap;
  int MAX_SIZE = randInt(20, 750);
  int MAX_RAND_NUM = randInt(MAX_SIZE, MAX_SIZE*100);
  auto getValue = [&stdMap](int a) -> int {
    auto iter = stdMap.find(a);
    if (iter != stdMap.end()) {return iter->second;}
    else return std::numeric_limits<int>::infinity();
  };

  auto getKeys = [&stdMap]() -> std::vector<int> {
    std::vector<int> keys;
    keys.reserve(stdMap.size());
    for(auto kv : stdMap) { keys.push_back(kv.first); }
    return keys;
  };

  auto printKeysValues = [&stdMap]() -> void {
	std::cout << "[ ";
    for(auto const& pair : stdMap) { std::cout << "{" << pair.first << "," << pair.second << "},"; }
    std::cout << " ]";
  };

  for (int loop = 0; loop < LOOPS; loop++) {

    map.clear();
    stdMap.clear();
    ASSERT_TRUE(map.isEmpty());

    std::vector<int> rand_nums = genRandList(-MAX_RAND_NUM, MAX_RAND_NUM, MAX_SIZE);
    auto containsNum = [&rand_nums](int a) -> bool { auto iter = std::find(rand_nums.begin(), rand_nums.end(), a); return iter != rand_nums.end(); };

    for (auto key : rand_nums) { map.add(key, key); stdMap.insert({key,key}); }

//    std::cout << "MAP: " << std::endl;
//    std::cout << map << std::endl;
//    std::cout << "MAP2: " << std::endl;
//    printKeysValues();
//    std::cout << std::endl;

//    std::cout << "KEYS:";
    for (int key : map) {
//        std::cout << key << "," << std::endl;
      ASSERT_EQ(key, map.get(key));
      int val = getValue(key);
      ASSERT_EQ(map.get(key), val);
      ASSERT_TRUE(map.hasKey(key));
      ASSERT_TRUE(containsNum(key));
    }
//    std::cout << std::endl;


    for (int key : getKeys()) {
      ASSERT_EQ(key, map.get(key));
    }

  }
}


TEST(HashTableLinearProbingTest, testConcurrentModificationException) {
  try {
    HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>();
    map.add(1, 1);
    map.add(2, 1);
    map.add(3, 1);
    map.add(4, 1);
    map.add(5, 1);
    for (int key : map) { map.add(7, 7); }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(HashTableLinearProbingTest, testConcurrentModificationException2) {
  try {
    HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>();
    map.add(1, 1);
    map.add(2, 1);
    map.add(3, 1);
    map.add(4, 1);
    map.add(5, 1);
    for (int key : map) { map.remove(2); }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(HashTableLinearProbingTest, randomRemove) {

  std::unordered_set<int> stdKeysSet;
  HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>();
  int MAX_SIZE = randInt(20, 750);
  int MAX_RAND_NUM = randInt(MAX_SIZE, MAX_SIZE*100);

  for (int loop = 0; loop < LOOPS; loop++) {

    map.clear();
    stdKeysSet.clear();

    // Add some random values
    for (int i = 0; i < MAX_SIZE; i++) {
      int randomVal = randInt(-MAX_RAND_NUM, MAX_RAND_NUM);
//      std::cout << "loop2{" << loop << "}MAX_SIZE{" << MAX_SIZE << "}MAX_RAND_NUM{" << MAX_RAND_NUM << "}randomVal{" << randomVal << "}" << std::endl;

      stdKeysSet.insert(randomVal);
      map.put(randomVal, 5);
    }

    ASSERT_EQ(map.size(), stdKeysSet.size());

    std::vector<int> keys = map.keys();
//    std::cout << "keys{";
//    for (auto key : keys) std::cout << key << ","; map.remove(key);
//    std::cout << "}" << std::endl;

    for (auto key : keys) map.del(key);
    ASSERT_TRUE(map.isEmpty());
  }
}


TEST(HashTableLinearProbingTest, removeTest) {

  HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>(7);

  // Add three elements
  map.put(11, 0);
  map.put(12, 0);
  map.put(13, 0);
  ASSERT_EQ(3, map.size());

  // Add ten more
  for (int i = 1; i <= 10; i++) map.put(i, 0);
  ASSERT_EQ(13, map.size());

  // Remove ten
  for (int i = 1; i <= 10; i++) map.del(i);
  ASSERT_EQ(3, map.size());

  // remove three
  map.del(11);
  map.del(12);
  map.del(13);
  ASSERT_EQ(0, map.size());

}


TEST(HashTableLinearProbingTest, testRandomMapOperations) {

  std::unordered_map<int, int> stdMap;
  HashTableLinearProbing<int, int> map = HashTableLinearProbing<int, int>();

  auto containsKey = [&stdMap](int a) -> bool { auto iter = stdMap.find(a); return iter != stdMap.end(); };
  auto getValue = [&stdMap](int a) -> int {
    auto iter = stdMap.find(a);
    if (iter != stdMap.end()) {return iter->second;}
    else return std::numeric_limits<int>::infinity();
  };

  for (int loop = 0; loop < LOOPS; loop++) {
    map.clear();
    stdMap.clear();
    ASSERT_EQ(stdMap.size(), map.size());

    double probability1 = randDouble(0., 1.);
    double probability2 = randDouble(0., 1.);

    int MAX_SIZE = randInt(20, 750);
    int MAX_RAND_NUM = randInt(MAX_SIZE, MAX_SIZE*100);

//    std::cout << "loop{" << loop << "}MAX_SIZE{" << MAX_SIZE << "}MAX_RAND_NUM{" << MAX_RAND_NUM << "}" << std::endl;

    std::vector<int> nums = genRandList(-MAX_RAND_NUM, MAX_RAND_NUM, MAX_SIZE);
    for (unsigned i = 0; i < nums.size(); i++) {
      double r = randDouble(0., 1.);

      int key = nums[i];
      int val = i;
      if (r < probability1) {
//        std::cout << "add{" << key << "," << val << "}" << std::endl;
        stdMap.insert({key, val});
        map.put(key, val);

        val = getValue(key);
        ASSERT_EQ(val, map.get(key));
      }
      ASSERT_EQ(containsKey(key), map.containsKey(key));
      ASSERT_EQ(stdMap.size(), map.size());

      if (r > probability2) {
        map.remove(key);
        stdMap.erase(key);
      }

      val = getValue(key);
      ASSERT_EQ(val, map.get(key));
      ASSERT_EQ(containsKey(key), map.containsKey(key));
      ASSERT_EQ(stdMap.size(), map.size());
    }
  }
}

#endif
} // namespace dsa
} // namespace dsa
