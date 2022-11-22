#pragma once

#include <string>


#include <cstring>
#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h> 
#include <unistd.h>
#endif


using namespace std;

#include "json.hpp"

using json = nlohmann::json;

//消息编号定义
#ifndef MSG_ID_LIST
#define MSG_ID_LIST 1
//REQUEST
#define DEV_STATUS_UPDATE 50006
#define DEV_ROUTE_PROGRESS 50009
#define DEV_POWERON 55002
#define DEV_SHUTDOWN 55003
#define DEV_ARM 55021
#define DEV_DISARM 55022
#define DEV_TAKEOFF 55004
#define DEV_GOBACK 55006
#define DEV_HOLD 55017
#define DEV_NEWROUTE 55010
#define DEV_GOROUTE 55011

#define DEV_GIMBAL 50033
#define DEV_RADAR 50034
#define DEV_STATUS_MOVEOBJ 50035
#define DEV_STATUS_GIMBAL 50036
#define DEV_STATUS_TARGET 50037

//RESPONSE
#define DEV_STATUS_UPDATE_RESPONSE 60006
#define DEV_ROUTE_PROGRESS_RESPONSE 60009
#define DEV_POWERON_RESPONSE 65002
#define DEV_SHUTDOWN_RESPONSE 65003
#define DEV_ARM_RESPONSE 65021
#define DEV_DISARM_RESPONSE 65022
#define DEV_TAKEOFF_RESPONSE 65004
#define DEV_GOBACK_RESPONSE 65006
#define DEV_HOLD_RESPONSE 65017
#define DEV_NEWROUTE_RESPONSE 65010
#define DEV_GOROUTE_RESPONSE 65011

#define DEV_GIMBAL_RESPONSE 60033
#define DEV_RADAR_RESPONSE 60034
#define DEV_STATUS_MOVEOBJ_RESPONSE 60035
#define DEV_STATUS_GIMBAL_RESPONSE 60036
#define DEV_STATUS_TARGET_RESPONSE 60037

#endif

/**
请求回报的state状态值
*/
enum State {
	/** 失败 */
	FAIL = 0,
	/** 成功 */
	SUCCESS = 1,
	/** 异常 */
	EXCEPTION = 2,
	/** 推送 */
	PUSH = 3,
	/** 未登陆 */
	REDIRECT = 4,
	/** 阻塞, 没有失败, 但是事情需要延后 */
	BLOCK = 5,
	/** 主动发送 */
	CODE = 6,
	/** 特殊状态 */
	SPECIAL = 7,
	/** 指令重复 */
	REPEAT = 8,
	/** 被禁止访问 */
	FORBIDDEN = 9,
};

class JsonBase{
public:
	JsonBase(){};
	virtual ~JsonBase(){};
public:
	virtual JsonBase* parseFromJson(const json& json){return NULL;};
	virtual char* toJsonString(){return NULL;};
	virtual void toJson(json &jsonObj){};

#define DEV_STATUS_UPDATE 50006
#define DEV_ROUTE_PROGRESS 50009
#define DEV_POWERON 55002
#define DEV_SHUTDOWN 55003
#define DEV_ARM 55021
#define DEV_DISARM 55022
#define DEV_TAKEOFF 55004
#define DEV_GOBACK 55006
#define DEV_HOLD 55017
#define DEV_NEWROUTE 55010
#define DEV_GOROUTE 55011

#define DEV_GIMBAL 50033
#define DEV_RADAR 50034
#define DEV_STATUS_MOVEOBJ 50035
#define DEV_STATUS_GIMBAL 50036
#define DEV_STATUS_TARGET 50037

	//RESPONSE
#define BASE_RESPONSE 60000
#define DEV_STATUS_UPDATE_RESPONSE 60006
#define DEV_ROUTE_PROGRESS_RESPONSE 60009
#define DEV_POWERON_RESPONSE 65002
#define DEV_SHUTDOWN_RESPONSE 65003
#define DEV_ARM_RESPONSE 65021
#define DEV_DISARM_RESPONSE 65022
#define DEV_TAKEOFF_RESPONSE 65004
#define DEV_GOBACK_RESPONSE 65006
#define DEV_HOLD_RESPONSE 65017
#define DEV_NEWROUTE_RESPONSE 65010
#define DEV_GOROUTE_RESPONSE 65011

#define DEV_GIMBAL_RESPONSE 60033
#define DEV_RADAR_RESPONSE 60034
#define DEV_STATUS_MOVEOBJ_RESPONSE 60035
#define DEV_STATUS_GIMBAL_RESPONSE 60036
#define DEV_STATUS_TARGET_RESPONSE 60037
	/** 返回结果不需要释放 */
	static const char *getMsgName(int mid) {
		switch(mid){
		case DEV_STATUS_UPDATE: return "DEV_STATUS_UPDATE";
		case DEV_ROUTE_PROGRESS: return "DEV_ROUTE_PROGRESS";
		case DEV_POWERON: return "DEV_POWERON";
		case DEV_SHUTDOWN: return "DEV_SHUTDOWN";
		case DEV_ARM: return "DEV_ARM";
		case DEV_DISARM: return "DEV_DISARM";
		case DEV_TAKEOFF: return "DEV_TAKEOFF";
		case DEV_GOBACK: return "DEV_GOBACK";
		case DEV_HOLD: return "DEV_HOLD";
		case DEV_NEWROUTE: return "DEV_NEWROUTE";
		case DEV_GOROUTE: return "DEV_GOROUTE";
		case DEV_GIMBAL: return "DEV_GIMBAL";
		case DEV_RADAR: return "DEV_RADAR";
		case DEV_STATUS_MOVEOBJ: return "DEV_STATUS_MOVEOBJ";
		case DEV_STATUS_GIMBAL: return "DEV_STATUS_GIMBAL";
		case DEV_STATUS_TARGET: return "DEV_STATUS_TARGET";
			//
		case DEV_STATUS_UPDATE_RESPONSE: return "DEV_STATUS_UPDATE_RESPONSE";
		case DEV_ROUTE_PROGRESS_RESPONSE: return "DEV_ROUTE_PROGRESS_RESPONSE";
		case DEV_POWERON_RESPONSE: return "DEV_POWERON_RESPONSE";
		case DEV_SHUTDOWN_RESPONSE: return "DEV_SHUTDOWN_RESPONSE";
		case DEV_ARM_RESPONSE: return "DEV_ARM_RESPONSE";
		case DEV_DISARM_RESPONSE: return "DEV_DISARM_RESPONSE";
		case DEV_TAKEOFF_RESPONSE: return "DEV_TAKEOFF_RESPONSE";
		case DEV_GOBACK_RESPONSE: return "DEV_GOBACK_RESPONSE";
		case DEV_HOLD_RESPONSE: return "DEV_HOLD_RESPONSE";
		case DEV_NEWROUTE_RESPONSE: return "DEV_NEWROUTE_RESPONSE";
		case DEV_GOROUTE_RESPONSE: return "DEV_GOROUTE_RESPONSE";
		case DEV_GIMBAL_RESPONSE: return "DEV_GIMBAL_RESPONSE";
		case DEV_RADAR_RESPONSE: return "DEV_RADAR_RESPONSE";
		case DEV_STATUS_MOVEOBJ_RESPONSE: return "DEV_STATUS_MOVEOBJ_RESPONSE";
		case DEV_STATUS_GIMBAL_RESPONSE: return "DEV_STATUS_GIMBAL_RESPONSE";
		case DEV_STATUS_TARGET_RESPONSE: return "DEV_STATUS_TARGET_RESPONSE";
		default: return NULL;
		}
	}
	static int getMsgId(const char *name){
		if(!name){
			printf("JsonBase::getMsgId: 参数不能为空!\n");
			return -1;
		}
		if (strcmp(name, "DEV_STATUS_UPDATE") == 0) { return DEV_STATUS_UPDATE; }
		else if (strcmp(name, "DEV_ROUTE_PROGRESS") == 0) { return DEV_ROUTE_PROGRESS; }
		else if (strcmp(name, "DEV_POWERON") == 0) { return DEV_POWERON; }
		else if (strcmp(name, "DEV_SHUTDOWN") == 0) { return DEV_SHUTDOWN; }
		else if (strcmp(name, "DEV_ARM") == 0) { return DEV_ARM; }
		else if (strcmp(name, "DEV_DISARM") == 0) { return DEV_DISARM; }
		else if (strcmp(name, "DEV_TAKEOFF") == 0) { return DEV_TAKEOFF; }
		else if (strcmp(name, "DEV_GOBACK") == 0) { return DEV_GOBACK; }
		else if (strcmp(name, "DEV_HOLD") == 0) { return DEV_HOLD; }
		else if (strcmp(name, "DEV_NEWROUTE") == 0) { return DEV_NEWROUTE; }
		else if (strcmp(name, "DEV_GOROUTE") == 0) { return DEV_GOROUTE; }
		else if (strcmp(name, "DEV_GIMBAL") == 0) { return DEV_GIMBAL; }
		else if (strcmp(name, "DEV_RADAR") == 0) { return DEV_RADAR; }
		else if (strcmp(name, "DEV_STATUS_MOVEOBJ") == 0) { return DEV_STATUS_MOVEOBJ; }
		else if (strcmp(name, "DEV_STATUS_GIMBAL") == 0) { return DEV_STATUS_GIMBAL; }
		else if (strcmp(name, "DEV_STATUS_TARGET") == 0) { return DEV_STATUS_TARGET; }
		//
		else if (strcmp(name, "DEV_STATUS_UPDATE_RESPONSE") == 0) { return DEV_STATUS_UPDATE_RESPONSE; }
		else if (strcmp(name, "DEV_ROUTE_PROGRESS_RESPONSE") == 0) { return DEV_ROUTE_PROGRESS_RESPONSE; }
		else if (strcmp(name, "DEV_POWERON_RESPONSE") == 0) { return DEV_POWERON_RESPONSE; }
		else if (strcmp(name, "DEV_SHUTDOWN_RESPONSE") == 0) { return DEV_SHUTDOWN_RESPONSE; }
		else if (strcmp(name, "DEV_ARM_RESPONSE") == 0) { return DEV_ARM_RESPONSE; }
		else if (strcmp(name, "DEV_DISARM_RESPONSE") == 0) { return DEV_DISARM_RESPONSE; }
		else if (strcmp(name, "DEV_TAKEOFF_RESPONSE") == 0) { return DEV_TAKEOFF_RESPONSE; }
		else if (strcmp(name, "DEV_GOBACK_RESPONSE") == 0) { return DEV_GOBACK_RESPONSE; }
		else if (strcmp(name, "DEV_HOLD_RESPONSE") == 0) { return DEV_HOLD_RESPONSE; }
		else if (strcmp(name, "DEV_NEWROUTE_RESPONSE") == 0) { return DEV_NEWROUTE_RESPONSE; }
		else if (strcmp(name, "DEV_GOROUTE_RESPONSE") == 0) { return DEV_GOROUTE_RESPONSE; }
		else if (strcmp(name, "DEV_GIMBAL_RESPONSE") == 0) { return DEV_GIMBAL_RESPONSE; }
		else if (strcmp(name, "DEV_RADAR_RESPONSE") == 0) { return DEV_RADAR_RESPONSE; }
		else if (strcmp(name, "DEV_STATUS_MOVEOBJ_RESPONSE") == 0) { return DEV_STATUS_MOVEOBJ_RESPONSE; }
		else if (strcmp(name, "DEV_STATUS_GIMBAL_RESPONSE") == 0) { return DEV_STATUS_GIMBAL_RESPONSE; }
		else if (strcmp(name, "DEV_STATUS_TARGET_RESPONSE") == 0) { return DEV_STATUS_TARGET_RESPONSE; }
		return -1;
	}

	static std::map<std::string, std::string>* getErrorMap(const char *error){
		if(!error)
			return NULL;
		std::map<std::string, std::string> *data = new std::map<std::string,std::string>();
		std::string msg = error;
		data->insert(std::pair<std::string,std::string>("msg", msg));
		return data;
	}

};

/**
 * 消息编号辅助函数
 */
class MsgIdUtil {
public:
	MsgIdUtil() {};
	~MsgIdUtil() {};
public:
	//根据请求消息编号, 获取响应消息编号
	static int getResponseMsgId(int requestMsgId) {
		return requestMsgId + 10000;
	}
	//根据响应消息编号, 获取请求消息编号
	static int getRequestMsgId(int responseMsgId) {
		return responseMsgId - 10000;
	}
};


