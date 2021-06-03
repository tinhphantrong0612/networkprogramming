#pragma once

/* The getTime function get the current time
* @return	mili-seconds since 00:00:00 01/01/1970
*/
long long getTime() {
	struct timespec timeSpec;
	timespec_get(&timeSpec, TIME_UTC);
	return 1000 * timeSpec.tv_sec + timeSpec.tv_nsec / 1000000;
}