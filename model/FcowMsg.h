#pragma once

#include "BaseFcowTypes.h"

/** 引入通信原型类及空间 */
#include "Common.h"
#include "General.h"
#include "Usp.h"

/**
 * 默认的参数名称, 一般一条指令只需要一个参数结构体
 */
#ifndef DEFAULT_PARA
#define DEFAULT_PARA "para"
#endif

class FcowMsg {
public:
	int mid = -1;
	std::string src;
	JsonBase *data = NULL;
	long long time = 0;
public:
	FcowMsg();
	FcowMsg(int _mid);
	FcowMsg(int _mid, std::string target);
	virtual ~FcowMsg() {
		if(data){
			delete data;
			data = NULL;
		}
	}
	/*FcowMsg(){};
	FcowMsg(int _mid){
		this->mid = _mid;
	};
	FcowMsg(int _mid, std::string target){
		this->mid = _mid;
		this->src = target;
	};
	virtual ~FcowMsg(){
		// 开始释放对象
		if(data) {
			//对象类型指针约定使用new初始化, delete释放
			delete data;
			data = NULL;
		}
	};*/
public:
	/** 注意: 返回结果需要delete释放! */
	FcowMsg* parseFromJson(const json& json);
	/** 注意: 返回结果需要free释放! */
	char* toJsonString();
};