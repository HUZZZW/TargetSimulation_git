/*******************************************************************************
 * 版权所有 2017-2018 www.fcow-it.com
 * 构建时间: 2022-03-10
 * ClassUtil
 * 1.0
 *******************************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <array>
#include <ciso646>
#include <forward_list>
#include <iterator>
#include <map>
#include <vector>
#include <set>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <valarray>

#include "BaseFcowTypes.h"

#include "FcowUtil.h"

//nlohmann/json
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

#include "Common.h"

#include "General.h"

namespace schedule {
/**
通用基础数据类定义。
用于红外图像模拟模块内部软件之间的通信，
支持外部软件通过本协议控制仿真软件，或从仿真软件接收遥测信息。
2022-03-10, mqzhao
*/



/******************* 2022.新设计 *********************/

/** 设备状态上报对象. 存储使用Common.DroneStatus对象. 消息编号：50006. 响应消息编号: 60006. */
class FcowDroneStatusPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {50006};
    /** 民航局注册号 */
    string regno;
    /** cpn编号 */
    string cpn;
    /** 飞行动态信息 */
    FcowDroneInfoDynamic *info = NULL;
    /** 设备位置状态 */
    FcowDronePoint *pos = NULL;
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t sn;
    /** 兼容某型自动机场，暂未使用, 机场整型编号 */
    int32_t airportSn;
    /** 兼容某型自动机场，暂未使用, 飞机当前状态, 01=做好起飞准备; 02=起飞成功; 03=被机场回收成功; 04=正在下载; 05=下载成功; */
    int32_t state;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneStatusPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("cpn")) {
            cpn = jsonObj["cpn"];
        }
        if(jsonObj.contains("info")) {
            info = new FcowDroneInfoDynamic();
            info->parseFromJson(jsonObj["info"]);
        }
        if(jsonObj.contains("pos")) {
            pos = new FcowDronePoint();
            pos->parseFromJson(jsonObj["pos"]);
        }
        if(jsonObj.contains("sn")) {
            sn = jsonObj["sn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("state")) {
            state = jsonObj["state"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(!cpn.empty()) {
            jsonObj["cpn"] = cpn;
        }
        if(info) {
            json subJsonOfInfo;
            info->toJson(subJsonOfInfo);
            jsonObj["info"] = subJsonOfInfo;
        }
        if(pos) {
            json subJsonOfPos;
            pos->toJson(subJsonOfPos);
            jsonObj["pos"] = subJsonOfPos;
        }
        jsonObj["sn"] = sn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["state"] = state;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneStatusPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(!cpn.empty()) {
            jsonObj["cpn"] = cpn;
        }
        if(info) {
            json subJsonOfInfo;
            info->toJson(subJsonOfInfo);
            jsonObj["info"] = subJsonOfInfo;
        }
        if(pos) {
            json subJsonOfPos;
            pos->toJson(subJsonOfPos);
            jsonObj["pos"] = subJsonOfPos;
        }
        jsonObj["sn"] = sn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["state"] = state;

        return;
    }
public:
    FcowDroneStatusPara() {
        sn = 0;
        airportSn = 0;
        state = 0;
    }
    virtual ~FcowDroneStatusPara() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(info) {
            delete info;
        }
        //对象类型指针约定使用new初始化, delete释放
        if(pos) {
            delete pos;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 设备状态上报对象. 整型格式. 存储使用Common.DroneStatus对象. 消息编号：50006. 响应消息编号: 60006.
*/
class FcowDroneStatusIntPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {50006};
    /** 民航局注册号 */
    string regno;
    /** cpn编号 */
    string cpn;
    /** 飞行动态信息 */
    FcowDroneInfoDynamicInt *info = NULL;
    /** 设备位置状态 */
    FcowDronePointInt *pos = NULL;
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t sn;
    /** 兼容某型自动机场，暂未使用, 机场整型编号 */
    int32_t airportSn;
    /** 兼容某型自动机场，暂未使用, 飞机当前状态, 01=做好起飞准备; 02=起飞成功; 03=被机场回收成功; 04=正在下载; 05=下载成功; */
    int32_t state;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneStatusIntPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("cpn")) {
            cpn = jsonObj["cpn"];
        }
        if(jsonObj.contains("info")) {
            info = new FcowDroneInfoDynamicInt();
            info->parseFromJson(jsonObj["info"]);
        }
        if(jsonObj.contains("pos")) {
            pos = new FcowDronePointInt();
            pos->parseFromJson(jsonObj["pos"]);
        }
        if(jsonObj.contains("sn")) {
            sn = jsonObj["sn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("state")) {
            state = jsonObj["state"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(!cpn.empty()) {
            jsonObj["cpn"] = cpn;
        }
        if(info) {
            json subJsonOfInfo;
            info->toJson(subJsonOfInfo);
            jsonObj["info"] = subJsonOfInfo;
        }
        if(pos) {
            json subJsonOfPos;
            pos->toJson(subJsonOfPos);
            jsonObj["pos"] = subJsonOfPos;
        }
        jsonObj["sn"] = sn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["state"] = state;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneStatusIntPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(!cpn.empty()) {
            jsonObj["cpn"] = cpn;
        }
        if(info) {
            json subJsonOfInfo;
            info->toJson(subJsonOfInfo);
            jsonObj["info"] = subJsonOfInfo;
        }
        if(pos) {
            json subJsonOfPos;
            pos->toJson(subJsonOfPos);
            jsonObj["pos"] = subJsonOfPos;
        }
        jsonObj["sn"] = sn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["state"] = state;

        return;
    }
public:
    FcowDroneStatusIntPara() {
        sn = 0;
        airportSn = 0;
        state = 0;
    }
    virtual ~FcowDroneStatusIntPara() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(info) {
            delete info;
        }
        //对象类型指针约定使用new初始化, delete释放
        if(pos) {
            delete pos;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 航线执行进度通知, 用于设备端通知遥测接收软件. 消息编号：50009. 响应消息编号: 60009 */
class FcowDroneRouteProgressPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {50009};
    /** 设备注册号 */
    string regno;
    /** cpn鉴权凭证 */
    string cpn;
    /** 进度信息 */
    FcowDroneRouteProgress *prog = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneRouteProgressPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("cpn")) {
            cpn = jsonObj["cpn"];
        }
        if(jsonObj.contains("prog")) {
            prog = new FcowDroneRouteProgress();
            prog->parseFromJson(jsonObj["prog"]);
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(!cpn.empty()) {
            jsonObj["cpn"] = cpn;
        }
        if(prog) {
            json subJsonOfProg;
            prog->toJson(subJsonOfProg);
            jsonObj["prog"] = subJsonOfProg;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneRouteProgressPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(!cpn.empty()) {
            jsonObj["cpn"] = cpn;
        }
        if(prog) {
            json subJsonOfProg;
            prog->toJson(subJsonOfProg);
            jsonObj["prog"] = subJsonOfProg;
        }

        return;
    }
public:
    FcowDroneRouteProgressPara() {
    }
    virtual ~FcowDroneRouteProgressPara() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(prog) {
            delete prog;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 设备启动命令. 消息编号：55002. 响应消息编号: 65002 */
class FcowDronePowerOnPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55002};
    /** 设备注册号 */
    string regno;
    /** cpn编号 */
    string cpn;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDronePowerOnPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("cpn")) {
            cpn = jsonObj["cpn"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(!cpn.empty()) {
            jsonObj["cpn"] = cpn;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDronePowerOnPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(!cpn.empty()) {
            jsonObj["cpn"] = cpn;
        }

        return;
    }
public:
    FcowDronePowerOnPara() {
    }
    virtual ~FcowDronePowerOnPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 设备关闭命令. 消息编号：55003. 响应消息编号: 65003 */
class FcowDroneShutDownPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55003};
    /** 指定关闭的设备 部件 */
    int32_t target;
    /** 指定关闭的设备标识 */
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneShutDownPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("target")) {
            target = jsonObj["target"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["target"] = target;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneShutDownPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["target"] = target;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    FcowDroneShutDownPara() {
        target = 0;
    }
    virtual ~FcowDroneShutDownPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 松刹车，解锁或启动螺旋桨. 消息编号：55021. 响应消息编号: 65021 */
class FcowDroneArmPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55021};
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t devSn;
    /** 兼容某型自动机场，暂未使用, 机场编号 */
    int32_t airportSn;
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneArmPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneArmPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    FcowDroneArmPara() {
        devSn = 0;
        airportSn = 0;
    }
    virtual ~FcowDroneArmPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 刹车，锁定或停止螺旋桨. 消息编号：55022. 响应消息编号: 65022 */
class FcowDroneDisarmPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55022};
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t devSn;
    /** 兼容某型自动机场，暂未使用, 机场编号 */
    int32_t airportSn;
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneDisarmPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneDisarmPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    FcowDroneDisarmPara() {
        devSn = 0;
        airportSn = 0;
    }
    virtual ~FcowDroneDisarmPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 起飞命令, 设备接到命令后立即起飞. 消息编号：55004. 响应消息编号: 65004 */
class FcowDroneTakeoffPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55004};
    /** 可选参数, 起飞到指定离地高度, 如果不指定那么起飞高度由飞控自行确定 */
    float ht;
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t devSn;
    /** 兼容某型自动机场，暂未使用, 机场编号 */
    int32_t airportSn;
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneTakeoffPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("ht")) {
            ht = jsonObj["ht"];
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["ht"] = ht;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneTakeoffPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["ht"] = ht;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    FcowDroneTakeoffPara() {
        ht = 0;
        devSn = 0;
        airportSn = 0;
    }
    virtual ~FcowDroneTakeoffPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 返航命令, 设备接到命令后返航. 消息编号：55006. 响应消息编号: 65006 */
class FcowDroneGoBackPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55006};
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t devSn;
    /** 兼容某型自动机场，暂未使用, 机场编号 */
    int32_t airportSn;
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneGoBackPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneGoBackPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    FcowDroneGoBackPara() {
        devSn = 0;
        airportSn = 0;
    }
    virtual ~FcowDroneGoBackPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 悬停/盘旋. 消息编号：55017. 响应消息编号: 65017 */
class FcowDroneHoldPara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55017};
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t devSn;
    /** 兼容某型自动机场，暂未使用, 机场编号 */
    int32_t airportSn;
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneHoldPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneHoldPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    FcowDroneHoldPara() {
        devSn = 0;
        airportSn = 0;
    }
    virtual ~FcowDroneHoldPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 下发航线, 设备收到并保存, 等待后续执行命令. 消息编号：55010. 响应消息编号: 65010 */
class FcowDroneNewRoutePara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55010};
    /** 新航线 */
    FcowDroneRoute *route = NULL;
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t devSn;
    /** 兼容某型自动机场，暂未使用, 机场编号 */
    int32_t airportSn;
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneNewRoutePara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("route")) {
            route = new FcowDroneRoute();
            route->parseFromJson(jsonObj["route"]);
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(route) {
            json subJsonOfRoute;
            route->toJson(subJsonOfRoute);
            jsonObj["route"] = subJsonOfRoute;
        }
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneNewRoutePara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(route) {
            json subJsonOfRoute;
            route->toJson(subJsonOfRoute);
            jsonObj["route"] = subJsonOfRoute;
        }
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    FcowDroneNewRoutePara() {
        devSn = 0;
        airportSn = 0;
    }
    virtual ~FcowDroneNewRoutePara() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(route) {
            delete route;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 执行航线. 消息编号：55011. 响应消息编号: 65011 */
class FcowDroneGoRoutePara: public JsonBase {
public: 
    /** 头信息 */
    FcowHead head = {55011};
    /** 航线编号 */
    string routeId;
    /** 可选, 直接执行新航线 */
    FcowDroneRoute *route = NULL;
    /** 起始航点, 从0开始, 默认为0 */
    int startItem = 0;
    /** 兼容某型自动机场，暂未使用, 飞行器整型编号 */
    int32_t devSn;
    /** 兼容某型自动机场，暂未使用, 机场编号 */
    int32_t airportSn;
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneGoRoutePara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("routeId")) {
            routeId = jsonObj["routeId"];
        }
        if(jsonObj.contains("route")) {
            route = new FcowDroneRoute();
            route->parseFromJson(jsonObj["route"]);
        }
        if(jsonObj.contains("startItem")) {
            startItem = jsonObj["startItem"];
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!routeId.empty()) {
            jsonObj["routeId"] = routeId;
        }
        if(route) {
            json subJsonOfRoute;
            route->toJson(subJsonOfRoute);
            jsonObj["route"] = subJsonOfRoute;
        }
        jsonObj["startItem"] = startItem;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneGoRoutePara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!routeId.empty()) {
            jsonObj["routeId"] = routeId;
        }
        if(route) {
            json subJsonOfRoute;
            route->toJson(subJsonOfRoute);
            jsonObj["route"] = subJsonOfRoute;
        }
        jsonObj["startItem"] = startItem;
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    FcowDroneGoRoutePara() {
        devSn = 0;
        airportSn = 0;
    }
    virtual ~FcowDroneGoRoutePara() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(route) {
            delete route;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 吊舱精准控制 */
class UavGimbalCtrlPara: public JsonBase {
public: 
    FcowHead head = {50033};
    /** 设备登记号 */
    string regno;
    /** 设备整型编号, 后台填写 */
    int32_t devSn;
    /** 机场编号, 后台填写 */
    int32_t airportSn;
    /** 33: 云台向上， 34:云台向下, 35: 云台向左, 36: 云台向右, 37: 焦距拉伸绝对值, 默认焦距为1, 范围1~25 ,38:拍照1张, 39：开始录像, 40:停止录像*/
    int32_t dir;
    /** 偏移距离、角度, 米、度, 或者焦距倍数绝对值 */
    float offset=5;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual UavGimbalCtrlPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("dir")) {
            dir = jsonObj["dir"];
        }
        if(jsonObj.contains("offset")) {
            offset = jsonObj["offset"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["dir"] = dir;
        jsonObj["offset"] = offset;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("UavGimbalCtrlPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["dir"] = dir;
        jsonObj["offset"] = offset;

        return;
    }
public:
    UavGimbalCtrlPara() {
        devSn = 0;
        airportSn = 0;
        dir = 0;
    }
    virtual ~UavGimbalCtrlPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 精准飞行控制, 持续进行, 暂未启用*/
class UavGimbalCtrl2Para: public JsonBase {
public: 
    FcowHead head = {50033};
    /** 设备登记号 */
    string regno;
    /** 设备整型编号, 后台填写 */
    int32_t devSn;
    /** 机场编号, 后台填写 */
    int32_t airportSn;
    /** 33: 云台向上， 34:云台向下, 35: 云台向左, 36: 云台向右, 37: 图像放大, 38, 图像缩小 */
    int32_t dir;
    /** 1: 开始; 0: 结束 */
    float oper=0;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual UavGimbalCtrl2Para* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("dir")) {
            dir = jsonObj["dir"];
        }
        if(jsonObj.contains("oper")) {
            oper = jsonObj["oper"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["dir"] = dir;
        jsonObj["oper"] = oper;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("UavGimbalCtrl2Para 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["dir"] = dir;
        jsonObj["oper"] = oper;

        return;
    }
public:
    UavGimbalCtrl2Para() {
        devSn = 0;
        airportSn = 0;
        dir = 0;
    }
    virtual ~UavGimbalCtrl2Para() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 雷达模式、工作参数控制 */
class UavRadarCtrlPara: public JsonBase {
public: 
    FcowHead head = {50034};
    /** 设备登记号 */
    string regno;
    /** 设备整型编号, 后台填写 */
    int32_t devSn;
    /** 机场编号, 后台填写 */
    int32_t airportSn;
    /** 33: 雷达识别范围， 34:雷达扫描速度, */
    int32_t dir;
    /** 新的雷达范围、扫描速度值 */
    float offset=5;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual UavRadarCtrlPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("devSn")) {
            devSn = jsonObj["devSn"];
        }
        if(jsonObj.contains("airportSn")) {
            airportSn = jsonObj["airportSn"];
        }
        if(jsonObj.contains("dir")) {
            dir = jsonObj["dir"];
        }
        if(jsonObj.contains("offset")) {
            offset = jsonObj["offset"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["dir"] = dir;
        jsonObj["offset"] = offset;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("UavRadarCtrlPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["devSn"] = devSn;
        jsonObj["airportSn"] = airportSn;
        jsonObj["dir"] = dir;
        jsonObj["offset"] = offset;

        return;
    }
public:
    UavRadarCtrlPara() {
        devSn = 0;
        airportSn = 0;
        dir = 0;
    }
    virtual ~UavRadarCtrlPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 动态目标状态上报 */
class MoveObjectStatusPara: public JsonBase {
public: 
    FcowHead head = {50035};
    /** 设备登记号 */
    string regno;
    /** 运动目标的位置属性 */
    FcowDronePoint *moveObj = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual MoveObjectStatusPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("moveObj")) {
            moveObj = new FcowDronePoint();
            moveObj->parseFromJson(jsonObj["moveObj"]);
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(moveObj) {
            json subJsonOfMoveObj;
            moveObj->toJson(subJsonOfMoveObj);
            jsonObj["moveObj"] = subJsonOfMoveObj;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("MoveObjectStatusPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(moveObj) {
            json subJsonOfMoveObj;
            moveObj->toJson(subJsonOfMoveObj);
            jsonObj["moveObj"] = subJsonOfMoveObj;
        }

        return;
    }
public:
    MoveObjectStatusPara() {
    }
    virtual ~MoveObjectStatusPara() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(moveObj) {
            delete moveObj;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 红外吊舱状态上报 */
class UavGimbalStatusPara: public JsonBase {
public: 
    FcowHead head = {50036};
    /** 设备登记号 */
    string regno;
    /** 时间戳 毫秒 */
    int64_t time;
    /** 吊舱状态 */
    FuyaGimbal *gimbal = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual UavGimbalStatusPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("time")) {
            time = jsonObj["time"];
        }
        if(jsonObj.contains("gimbal")) {
            gimbal = new FuyaGimbal();
            gimbal->parseFromJson(jsonObj["gimbal"]);
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["time"] = time;
        if(gimbal) {
            json subJsonOfGimbal;
            gimbal->toJson(subJsonOfGimbal);
            jsonObj["gimbal"] = subJsonOfGimbal;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("UavGimbalStatusPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["time"] = time;
        if(gimbal) {
            json subJsonOfGimbal;
            gimbal->toJson(subJsonOfGimbal);
            jsonObj["gimbal"] = subJsonOfGimbal;
        }

        return;
    }
public:
    UavGimbalStatusPara() {
        time = 0;
    }
    virtual ~UavGimbalStatusPara() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(gimbal) {
            delete gimbal;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 目标检测结果上报 */
class TargetStatusPara: public JsonBase {
public: 
    FcowHead head = {50037};
    /** 设备登记号 */
    string regno;
    /** 设备整型编号, 后台填写 */
    vector<TargetPara*> *target = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual TargetStatusPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head.parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("target")) {
            target = new vector<TargetPara*>();
            for (auto& listItem : jsonObj["target"].items()){
                TargetPara *vinst = new TargetPara();
                vinst->parseFromJson(listItem.value());
                target->push_back(vinst);
            }
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(target) {
            for(auto &it : *target) {
                json subJsonOfIt149;
                it->toJson(subJsonOfIt149);
                jsonObj["target"].push_back(subJsonOfIt149);
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("TargetStatusPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        json subJsonOfHead;
        head.toJson(subJsonOfHead);
        jsonObj["head"] = subJsonOfHead;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        if(target) {
            for(auto &it : *target) {
                json subJsonOfIt580;
                it->toJson(subJsonOfIt580);
                jsonObj["target"].push_back(subJsonOfIt580);
            }
        }

        return;
    }
public:
    TargetStatusPara() {
    }
    virtual ~TargetStatusPara() {
        // 开始释放对象 
        if(target) {
            for(auto &it : *target) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete target;
        }
        //TODO, 在这里添加额外的释放处理
    }
};


} 
