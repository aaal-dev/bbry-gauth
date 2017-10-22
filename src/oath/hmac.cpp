// HMAC_SHA1 implementation
//
// Copyright 2010 Google Inc.
// Author: Markus Gutschke
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string.h>
#include "hmac.hpp"
#include "sha1.hpp"

void hmac_sha1(const uint8_t *key, int keyLength, const uint8_t *data, int dataLength, uint8_t *result, int resultLength) {
    SHA1_INFO ctx;
    uint8_t hashed_key[SHA1_DIGEST_LENGTH];
    if (keyLength > 64) {
        sha1_init(&ctx);
        sha1_update(&ctx, key, keyLength);
        sha1_final(&ctx, hashed_key);
        key = hashed_key;
        keyLength = SHA1_DIGEST_LENGTH;
    }

    uint8_t tmp_key[64];
    for (int i = 0; i < keyLength; ++i) {
        tmp_key[i] = key[i] ^ 0x36;
    }
    memset(tmp_key + keyLength, 0x36, 64 - keyLength);

    sha1_init(&ctx);
    sha1_update(&ctx, tmp_key, 64);
    sha1_update(&ctx, data, dataLength);
    uint8_t sha[SHA1_DIGEST_LENGTH];
    sha1_final(&ctx, sha);

    for (int i = 0; i < keyLength; ++i) {
        tmp_key[i] = key[i] ^ 0x5C;
    }
    memset(tmp_key + keyLength, 0x5C, 64 - keyLength);

    sha1_init(&ctx);
    sha1_update(&ctx, tmp_key, 64);
    sha1_update(&ctx, sha, SHA1_DIGEST_LENGTH);
    sha1_final(&ctx, sha);

    memset(result, 0, resultLength);
    if (resultLength > SHA1_DIGEST_LENGTH) {
        resultLength = SHA1_DIGEST_LENGTH;
    }
    memcpy(result, sha, resultLength);

    memset(hashed_key, 0, sizeof(hashed_key));
    memset(sha, 0, sizeof(sha));
    memset(tmp_key, 0, sizeof(tmp_key));
}
