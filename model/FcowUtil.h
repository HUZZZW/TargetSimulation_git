#pragma once

#include <string>


#include <cstring>
#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h> 
#include <unistd.h>
#endif
/** 工具类 */
class FcowUtil {
public:
	/**
	 * 当前时间字符串, 格式: 2018-11-12 10:00:00
	 */
	static const char* current_time() {
		static char now_time[32];
		static char usec_str[5];
		#ifdef WIN32
		return now_time;
		#else
		
		//获取时间
		time_t rawtime;
		struct tm* ltime;
		time(&rawtime);
		ltime = localtime((const time_t *)(&rawtime));
		//strftime(nowtime, 20, "%Y-%m-%d %H:%M:%S", ltime);

		//获取毫秒
		struct timeval tv;
		gettimeofday(&tv, NULL); //该函数在sys/time.h头文件中
		//sprintf(nowtime + 20, "%03d", tv.tv_usec / 1000);

		//一起写入缓存
		strftime(now_time, 20, "%Y-%m-%d %H:%M:%S", ltime);
		sprintf(usec_str, ".%03d", (int)(tv.tv_usec / 1000));
		strcat(now_time, usec_str);
		#endif
		return now_time;
	}

	/**
	 * 当前js时间戳
	 */
	static long long currentMillis() {
		//需要进行跨平台切换
		#ifdef WIN32
		return 0;
		#else
				//tv_usec的最大值是1000000，即1秒，记到1000000后，又会从0开始
				struct timeval tv;
				gettimeofday(&tv, NULL); //该函数在sys/time.h头文件中
				return ((int64_t)tv.tv_sec) * 1000 + ((int)tv.tv_usec) / 1000;
		#endif
		return 0;
	}
	

	};
