﻿#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "VLogger.h"
#include "VSha256.h"

void testString() {
  // 测试字符串
  std::string message = "This is a test message for SHA-256 calculation.";

  // 计算字符串的哈希值
  std::string hash_string_result = VSha256::Sha256->hash256(message);
  if (!hash_string_result.empty()) {
    // 预期的哈希值
    std::string expected_hash =
        "75e7ac0202eb971025b66b1ef13b84d16e596735ec13e20d6f549022eb2bce51";

    Log->logInfo("Expected SHA-256 hash: %s", expected_hash.c_str());
    Log->logInfo("Calculated SHA-256 hash: %s",
                          hash_string_result.c_str());

    // 比较预期的哈希值和计算得到的哈希值
    if (hash_string_result == expected_hash) {
      Log->logInfo("Hashes match.");
    } else {
      Log->logError("Hashes don't match.");
    }
  } else {
    Log->logError("Failed to calculate hash of string: %s",
                           message.c_str());
  }
}

void createTestFile(const std::string& filename, const std::string& data) {
  std::ofstream file(filename);
  if (!file) {
    Log->logError("Failed to create file: %s", filename.c_str());
    return;
  }
  file << data;
  file.close();
}

void testFile() {
  std::string filename = "test.txt";
  std::string message = "This is a test message for SHA-256 calculation.";
  std::string expected_hash =
      "75e7ac0202eb971025b66b1ef13b84d16e596735ec13e20d6f549022eb2bce51";
  VSha256 sha256;
  createTestFile(filename, message);
  sha256.updateFileHash(filename, 4096);
  std::string hash_result = sha256.digestToString();
  sha256.init();

  if (!hash_result.empty()) {
    Log->logInfo("File Expected SHA-256 hash: %s",
                          expected_hash.c_str());
    Log->logInfo("File Calculated SHA-256 hash: %s",
                          hash_result.c_str());

    if (hash_result == expected_hash) {
      Log->logInfo("File Hashes match.");
    } else {
      Log->logError("File Hashes don't match.");
    }
  }
}

int main() {
  testString();
  testFile();
  return 0;
}
