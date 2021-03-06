/*
 * Copyright (C) 2016 Team Win Recovery Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fscrypt_policy.h"
#include "fscrypt/fscrypt.h"

#define FS_KEY_DESCRIPTOR_SIZE 8

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Must specify a path\n");
		return -1;
	} else  {
#ifdef USE_FSCRYPT_POLICY_V1
		fscrypt_policy_v1 fep;
#else
		fscrypt_policy_v2 fep;
#endif
		if (fscrypt_policy_get_struct(argv[1], &fep)) {
#ifdef USE_FSCRYPT_POLICY_V1
			char policy_hex[FS_KEY_DESCRIPTOR_SIZE_HEX];
			bytes_to_hex(fep.master_key_descriptor, FS_KEY_DESCRIPTOR_SIZE, policy_hex);
#else
			char policy_hex[FSCRYPT_KEY_IDENTIFIER_HEX_SIZE];
			bytes_to_hex(fep.master_key_identifier, FSCRYPT_KEY_IDENTIFIER_SIZE, policy_hex);
#endif
			printf("%s\n", policy_hex);
		} else {
			printf("No policy set\n");
		}
	}
	return 0;
}
