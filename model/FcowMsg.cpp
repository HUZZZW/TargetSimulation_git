#include<stdio.h>
#include<stdlib.h>

#include "json.hpp"
#include "FcowMsg.h"


using namespace std;
using namespace schedule;

using json = nlohmann::json;

FcowMsg::FcowMsg() {
}

FcowMsg::FcowMsg(int _mid) {
	this->mid = _mid;
}
FcowMsg::FcowMsg(int _mid, std::string target) {
	this->mid = _mid;
	this->src = target;
}

/** 注意: 返回结果需要delete释放! */
FcowMsg* FcowMsg::parseFromJson(const json& json) {
	string jsonstr = json.dump();
	if(this->mid <= 0){
		if(json.contains("mid")){
			this->mid = json["mid"];
		}else if(json.contains("head")){
			this->mid = json["head"]["id"].get<int>();
			if(json["head"].contains("t"))
				this->time = json["head"]["t"].get<long long>();
		}else if(json.contains("data") && json["data"].contains("head")){
			this->mid = json["data"]["head"]["id"].get<int>();
			if(json["data"]["head"].contains("t"))
				this->time = json["data"]["head"]["t"].get<long long>();
		}
		if(this->mid <= 0){
			printf("FcowMsg::parseFromJson, 解析失败, mid不能为空, json=%s \n", jsonstr.c_str());
			return NULL;
		}
	}
	if(this->src.length() == 0){
		if(json.contains("src")){
			this->src = json["src"];
		}else if(json.contains("data") && json["data"].contains("src")){
			this->src = json["data"]["src"];
		}else{
			this->src = "";
		}
	}

	//指令解析
	JsonBase *res = NULL;
	switch(mid){
	// 来自企业端的USP命令
	case DEV_STATUS_UPDATE: res = new FcowDroneStatusPara(); break;
	case DEV_ROUTE_PROGRESS: res = new FcowDroneRouteProgressPara(); break;
	case DEV_POWERON: res = new FcowDronePowerOnPara(); break;
	case DEV_SHUTDOWN: res = new FcowDroneShutDownPara(); break;
	case DEV_ARM: res = new FcowDroneArmPara(); break;
	case DEV_DISARM: res = new FcowDroneDisarmPara(); break;
	case DEV_TAKEOFF: res = new FcowDroneTakeoffPara(); break;
	case DEV_GOBACK: res = new FcowDroneGoBackPara(); break;
	case DEV_HOLD: res = new FcowDroneHoldPara(); break;
	case DEV_NEWROUTE: res = new FcowDroneNewRoutePara(); break;
	case DEV_GOROUTE: res = new FcowDroneGoRoutePara(); break;
	// 
	case DEV_GIMBAL: res = new UavGimbalCtrlPara(); break;
	case DEV_RADAR: res = new UavRadarCtrlPara(); break;
	case DEV_STATUS_MOVEOBJ: res = new MoveObjectStatusPara(); break;
	case DEV_STATUS_GIMBAL: res = new UavGimbalStatusPara(); break;
	case DEV_STATUS_TARGET: res = new TargetStatusPara(); break;
	//new request

	//来自企业端的USP响应消息, 使用FcowServerFeedback解析
	case DEV_STATUS_UPDATE_RESPONSE: 
	case DEV_ROUTE_PROGRESS_RESPONSE: 
	case DEV_POWERON_RESPONSE:
	case DEV_SHUTDOWN_RESPONSE:
	case DEV_ARM_RESPONSE: 
	case DEV_DISARM_RESPONSE: 
	case DEV_TAKEOFF_RESPONSE:
	case DEV_GOBACK_RESPONSE: 
	case DEV_HOLD_RESPONSE:
	case DEV_NEWROUTE_RESPONSE:
	case DEV_GOROUTE_RESPONSE: 
	case DEV_GIMBAL_RESPONSE:
	case DEV_RADAR_RESPONSE:
	case DEV_STATUS_MOVEOBJ_RESPONSE:
	case DEV_STATUS_GIMBAL_RESPONSE:
	case DEV_STATUS_TARGET_RESPONSE:
		res = new FcowDroneFeedback();
		break;

	default:
		printf("无法解析的指令: %d \n", mid);
		return NULL;
	}
	//解析para对象
	//注意, 部分指令不带para对象, 因此不是必须
	if(res){
        if(json.contains("head")){
			res->parseFromJson(json);
		} else if(json.contains("data")){
			res->parseFromJson(json["data"]);
		}
		this->data = res;
	}
	return this;
}

/** 注意: 返回结果需要free释放! */
char* FcowMsg::toJsonString() {
	//build json
	json jsonObj;
	jsonObj["mid"] = mid;
	if(time > 0)
		jsonObj["time"] = time;
	if(src.length() > 0){
		jsonObj["src"] = src;
	}
	char *dataStr = NULL;
	if(data) {
		dataStr = data->toJsonString();
		jsonObj["data"] = json::parse(dataStr);
	}

	//to string
	std::string jsonStr = jsonObj.dump();
	int jsonLen = jsonStr.length();
	char *res = (char*)malloc(jsonLen+8);
	if(!res) {
		printf("FcowMsg::toJsonString: 内存不足!\n");
		return NULL;
	}
	memcpy(res, jsonStr.c_str(), jsonLen);
	res[jsonLen] = 0;

	if(dataStr){
		free(dataStr);
	}

	return res;
}

