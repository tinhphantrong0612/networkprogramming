#pragma once
extern map<string, pair<string, int>> accountMap;
/* The getTime function get the current time
* @return	mili-seconds since 00:00:00 01/01/1970
*/
long long getTime() {
	struct timespec timeSpec;
	timespec_get(&timeSpec, TIME_UTC);
	return 1000 * timeSpec.tv_sec + timeSpec.tv_nsec / 1000000;
}

void loadAccountMap(char *fileName) {
	FILE *accountFile;
	fopen_s(&accountFile, fileName, "r");
	char buff[BUFF_SIZE];
	char username[ACCOUNT_SIZE];
	char password[ACCOUNT_SIZE];
	while (fgets(buff, BUFF_SIZE, accountFile) != NULL) {
		sscanf_s(buff, "%s %s", username, ACCOUNT_SIZE, password, ACCOUNT_SIZE);
		accountMap[username] = make_pair(password, NOT_AUTHORIZED);
	}
	fclose(accountFile);
}

void addNewAccount(char *fileName, char *username, char *password) {
	FILE *accountFile;
	fopen_s(&accountFile, fileName, "a");
	fprintf_s(accountFile, "%s %s\n", username, password);
	fclose(accountFile);
}