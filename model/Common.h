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

#include "General.h"

namespace schedule {
/**
通用基础数据类定义。
2022-03-10, mqzhao
*/



/** 通用的通信头部, 所有消息都要附带 */
class FcowHead: public JsonBase {
public: 
    /** 消息号，32位整型 */
    int32_t id;
    /** 消息序号，32位整型，发送一条消息+1 */
    int32_t n;
    /** 北京时间戳, 单位毫秒，64位整型 */
    int64_t t;
    /** 消息来源，1：飞行器仿真，2：红外仿真，3：雷达仿真，4：红外图像生成，5：雷达图形生成，6：测试软件，7：增强视景 8, 其他系统, 消息来源只能设置一位 */
    int32_t r;
    /** 消息目标，1：飞行器仿真，2：红外仿真，3：雷达仿真，4：红外图像生成，5：雷达图形生成，6：测试软件，7：增强视景 8, 其他系统, 消息来源只能设置一位 */
    int32_t d;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowHead* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("id")) {
            id = jsonObj["id"];
        }
        if(jsonObj.contains("n")) {
            n = jsonObj["n"];
        }
        if(jsonObj.contains("t")) {
            t = jsonObj["t"];
        }
        if(jsonObj.contains("r")) {
            r = jsonObj["r"];
        }
        if(jsonObj.contains("d")) {
            d = jsonObj["d"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["id"] = id;
        jsonObj["n"] = n;
        jsonObj["t"] = t;
        jsonObj["r"] = r;
        jsonObj["d"] = d;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowHead 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["id"] = id;
        jsonObj["n"] = n;
        jsonObj["t"] = t;
        jsonObj["r"] = r;
        jsonObj["d"] = d;

        return;
    }
public:
    FcowHead() {
        id = 0;
        n = 0;
        t = 0;
        r = 0;
        d = 0;
    }
    FcowHead(int32_t _id) {
        id = 0;
        n = 0;
        t = 0;
        r = 0;
        d = 0;
        id = _id;
        t = FcowUtil::currentMillis();
    }
    virtual ~FcowHead() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

class FuyaGimbal: public JsonBase {
public: 
    /** 当前摄像头角度Roll(坐标轴为世界坐标轴，单位为度) */
    int32_t roll;
    /** 当前摄像头角度Pitch(坐标轴为世界坐标轴，单位为度) */
    int32_t pitch;
    /** 当前摄像头角度Yaw(坐标轴为世界坐标轴，单位为度) */
    int32_t yaw;
    /** 当前摄像头焦距 */
    int32_t focus;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FuyaGimbal* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("roll")) {
            roll = jsonObj["roll"];
        }
        if(jsonObj.contains("pitch")) {
            pitch = jsonObj["pitch"];
        }
        if(jsonObj.contains("yaw")) {
            yaw = jsonObj["yaw"];
        }
        if(jsonObj.contains("focus")) {
            focus = jsonObj["focus"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["roll"] = roll;
        jsonObj["pitch"] = pitch;
        jsonObj["yaw"] = yaw;
        jsonObj["focus"] = focus;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FuyaGimbal 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["roll"] = roll;
        jsonObj["pitch"] = pitch;
        jsonObj["yaw"] = yaw;
        jsonObj["focus"] = focus;

        return;
    }
public:
    FuyaGimbal() {
        roll = 0;
        pitch = 0;
        yaw = 0;
        focus = 0;
    }
    virtual ~FuyaGimbal() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 设备固有属性信息, 用于开机回传 */
class FcowDroneInfoDynamic: public JsonBase {
public: 
    /** 电池剩余电量百分比, [0,100] */
    int32_t bat;
    /** 燃油剩余量百分比, [0,100],或燃油数量,升 */
    int32_t fuel;
    /** 是否携带摄像头, 摄像头可能动态加载. 0:无摄像头, 1: 有摄像头 */
    int32_t cam;
    /** 马达是否启动. 0:未启动, 1:已启动 */
    int32_t arm;
    /** 是否已起飞到空中, 0: 在地上, 1: 在空中 */
    int32_t air;
    /** 电池电压 */
    float vol;
    /** 电池电流 */
    float batCurr;
    /** 当前绝对速度, 米/秒 */
    float absp;
    /** 环境温度,摄氏度 */
    float temp;
    /** 最大飞行速度, 米/秒 */
    int maxSpd;
    /** 返航爬升高度 */
    int retHt;
    /** 飞行任务完成后是否自动返航, 0: 不自动返航, 1: 自动返航 */
    int autoRet;
    /** 是否处于离线模式, 0:非离线模式, 1: 离线模式 */
    int offboard;
    /** 总航点数量 */
    int32_t total;
    /** 当前目标航点索引[0,total], 0表示启动飞行器出发 */
    int32_t curr;
    /** 执行是否完成 */
    int32_t over;
    /** 循环执行次数 */
    int32_t loop;
    /** 当前循环索引 */
    int32_t lpidx;
    /** 当前位置到下一个航点的距离, 单位米 */
    float dis;
    /** 当前飞行模式 */
    string mode;
    /** 活动类型：land-降落/track-轨迹记录 */
    string act;
    /** 当前故障码, trouble code */
    string tc;
    /** 针对复亚机场新增, 当前航线编号,两字节整型 */
    int32_t rid;
    /** 针对复亚机场新增, 当前是否开启直播录像 */
    int32_t recording;
    /** 针对复亚机场新增, 已拍摄照片数量 */
    int32_t snapNum;
    /** 针对复亚机场新增, 航线完成百分比 */
    int32_t routeRatio;
    /** 针对复亚机场新增, 云台相机的角度 */
    FuyaGimbal *gimbal = NULL;
    /** 针对复亚机场新增, 错误码,两字节整型, 16bit, 每个bit代表一种错误信息 */
    int32_t errcode;
    /** 适配复亚机场，00=不会自动发送  01=n hz  02=更新才发送 */
    int32_t autoUpdate;
    /** 针对复亚机场新增, 是否落地入库, 整型 */
    int32_t backhome;
    /** gps卫星数量 */
    int gpsSatNum;
    /** gps信号质量, 0~5 */
    int gpsLevel;
    /** 已飞行时长, 单位秒 */
    int flyTime;
    /** 飞行器头部当前方位 */
    int hdir;
    /** 遥控器与飞机之间的信号质量, 1~100 */
    int siglev = 0;
    /** 地面站位置 */
    LngLatHgtAlt *spos = NULL;
    /** SDK类型 */
    string sdk;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneInfoDynamic* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("bat")) {
            bat = jsonObj["bat"];
        }
        if(jsonObj.contains("fuel")) {
            fuel = jsonObj["fuel"];
        }
        if(jsonObj.contains("cam")) {
            cam = jsonObj["cam"];
        }
        if(jsonObj.contains("arm")) {
            arm = jsonObj["arm"];
        }
        if(jsonObj.contains("air")) {
            air = jsonObj["air"];
        }
        if(jsonObj.contains("vol")) {
            vol = jsonObj["vol"];
        }
        if(jsonObj.contains("batCurr")) {
            batCurr = jsonObj["batCurr"];
        }
        if(jsonObj.contains("absp")) {
            absp = jsonObj["absp"];
        }
        if(jsonObj.contains("temp")) {
            temp = jsonObj["temp"];
        }
        if(jsonObj.contains("maxSpd")) {
            maxSpd = jsonObj["maxSpd"];
        }
        if(jsonObj.contains("retHt")) {
            retHt = jsonObj["retHt"];
        }
        if(jsonObj.contains("autoRet")) {
            autoRet = jsonObj["autoRet"];
        }
        if(jsonObj.contains("offboard")) {
            offboard = jsonObj["offboard"];
        }
        if(jsonObj.contains("total")) {
            total = jsonObj["total"];
        }
        if(jsonObj.contains("curr")) {
            curr = jsonObj["curr"];
        }
        if(jsonObj.contains("over")) {
            over = jsonObj["over"];
        }
        if(jsonObj.contains("loop")) {
            loop = jsonObj["loop"];
        }
        if(jsonObj.contains("lpidx")) {
            lpidx = jsonObj["lpidx"];
        }
        if(jsonObj.contains("dis")) {
            dis = jsonObj["dis"];
        }
        if(jsonObj.contains("mode")) {
            mode = jsonObj["mode"];
        }
        if(jsonObj.contains("act")) {
            act = jsonObj["act"];
        }
        if(jsonObj.contains("tc")) {
            tc = jsonObj["tc"];
        }
        if(jsonObj.contains("rid")) {
            rid = jsonObj["rid"];
        }
        if(jsonObj.contains("recording")) {
            recording = jsonObj["recording"];
        }
        if(jsonObj.contains("snapNum")) {
            snapNum = jsonObj["snapNum"];
        }
        if(jsonObj.contains("routeRatio")) {
            routeRatio = jsonObj["routeRatio"];
        }
        if(jsonObj.contains("gimbal")) {
            gimbal = new FuyaGimbal();
            gimbal->parseFromJson(jsonObj["gimbal"]);
        }
        if(jsonObj.contains("errcode")) {
            errcode = jsonObj["errcode"];
        }
        if(jsonObj.contains("autoUpdate")) {
            autoUpdate = jsonObj["autoUpdate"];
        }
        if(jsonObj.contains("backhome")) {
            backhome = jsonObj["backhome"];
        }
        if(jsonObj.contains("gpsSatNum")) {
            gpsSatNum = jsonObj["gpsSatNum"];
        }
        if(jsonObj.contains("gpsLevel")) {
            gpsLevel = jsonObj["gpsLevel"];
        }
        if(jsonObj.contains("flyTime")) {
            flyTime = jsonObj["flyTime"];
        }
        if(jsonObj.contains("hdir")) {
            hdir = jsonObj["hdir"];
        }
        if(jsonObj.contains("siglev")) {
            siglev = jsonObj["siglev"];
        }
        if(jsonObj.contains("spos")) {
            spos = new LngLatHgtAlt();
            spos->parseFromJson(jsonObj["spos"]);
        }
        if(jsonObj.contains("sdk")) {
            sdk = jsonObj["sdk"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["bat"] = bat;
        jsonObj["fuel"] = fuel;
        jsonObj["cam"] = cam;
        jsonObj["arm"] = arm;
        jsonObj["air"] = air;
        jsonObj["vol"] = vol;
        jsonObj["batCurr"] = batCurr;
        jsonObj["absp"] = absp;
        jsonObj["temp"] = temp;
        jsonObj["maxSpd"] = maxSpd;
        jsonObj["retHt"] = retHt;
        jsonObj["autoRet"] = autoRet;
        jsonObj["offboard"] = offboard;
        jsonObj["total"] = total;
        jsonObj["curr"] = curr;
        jsonObj["over"] = over;
        jsonObj["loop"] = loop;
        jsonObj["lpidx"] = lpidx;
        jsonObj["dis"] = dis;
        if(!mode.empty()) {
            jsonObj["mode"] = mode;
        }
        if(!act.empty()) {
            jsonObj["act"] = act;
        }
        if(!tc.empty()) {
            jsonObj["tc"] = tc;
        }
        jsonObj["rid"] = rid;
        jsonObj["recording"] = recording;
        jsonObj["snapNum"] = snapNum;
        jsonObj["routeRatio"] = routeRatio;
        if(gimbal) {
            json subJsonOfGimbal;
            gimbal->toJson(subJsonOfGimbal);
            jsonObj["gimbal"] = subJsonOfGimbal;
        }
        jsonObj["errcode"] = errcode;
        jsonObj["autoUpdate"] = autoUpdate;
        jsonObj["backhome"] = backhome;
        jsonObj["gpsSatNum"] = gpsSatNum;
        jsonObj["gpsLevel"] = gpsLevel;
        jsonObj["flyTime"] = flyTime;
        jsonObj["hdir"] = hdir;
        jsonObj["siglev"] = siglev;
        if(spos) {
            json subJsonOfSpos;
            spos->toJson(subJsonOfSpos);
            jsonObj["spos"] = subJsonOfSpos;
        }
        if(!sdk.empty()) {
            jsonObj["sdk"] = sdk;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneInfoDynamic 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["bat"] = bat;
        jsonObj["fuel"] = fuel;
        jsonObj["cam"] = cam;
        jsonObj["arm"] = arm;
        jsonObj["air"] = air;
        jsonObj["vol"] = vol;
        jsonObj["batCurr"] = batCurr;
        jsonObj["absp"] = absp;
        jsonObj["temp"] = temp;
        jsonObj["maxSpd"] = maxSpd;
        jsonObj["retHt"] = retHt;
        jsonObj["autoRet"] = autoRet;
        jsonObj["offboard"] = offboard;
        jsonObj["total"] = total;
        jsonObj["curr"] = curr;
        jsonObj["over"] = over;
        jsonObj["loop"] = loop;
        jsonObj["lpidx"] = lpidx;
        jsonObj["dis"] = dis;
        if(!mode.empty()) {
            jsonObj["mode"] = mode;
        }
        if(!act.empty()) {
            jsonObj["act"] = act;
        }
        if(!tc.empty()) {
            jsonObj["tc"] = tc;
        }
        jsonObj["rid"] = rid;
        jsonObj["recording"] = recording;
        jsonObj["snapNum"] = snapNum;
        jsonObj["routeRatio"] = routeRatio;
        if(gimbal) {
            json subJsonOfGimbal;
            gimbal->toJson(subJsonOfGimbal);
            jsonObj["gimbal"] = subJsonOfGimbal;
        }
        jsonObj["errcode"] = errcode;
        jsonObj["autoUpdate"] = autoUpdate;
        jsonObj["backhome"] = backhome;
        jsonObj["gpsSatNum"] = gpsSatNum;
        jsonObj["gpsLevel"] = gpsLevel;
        jsonObj["flyTime"] = flyTime;
        jsonObj["hdir"] = hdir;
        jsonObj["siglev"] = siglev;
        if(spos) {
            json subJsonOfSpos;
            spos->toJson(subJsonOfSpos);
            jsonObj["spos"] = subJsonOfSpos;
        }
        if(!sdk.empty()) {
            jsonObj["sdk"] = sdk;
        }

        return;
    }
public:
    FcowDroneInfoDynamic() {
        bat = 0;
        fuel = 0;
        cam = 0;
        arm = 0;
        air = 0;
        vol = 0;
        batCurr = 0;
        absp = 0;
        temp = 0;
        maxSpd = 0;
        retHt = 0;
        autoRet = 0;
        offboard = 0;
        total = 0;
        curr = 0;
        over = 0;
        loop = 0;
        lpidx = 0;
        dis = 0;
        rid = 0;
        recording = 0;
        snapNum = 0;
        routeRatio = 0;
        errcode = 0;
        autoUpdate = 0;
        backhome = 0;
        gpsSatNum = 0;
        gpsLevel = 0;
        flyTime = 0;
        hdir = 0;
    }
    virtual ~FcowDroneInfoDynamic() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(gimbal) {
            delete gimbal;
        }
        //对象类型指针约定使用new初始化, delete释放
        if(spos) {
            delete spos;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 设备固有属性信息, 用于数据库存储精度测试 */
class FcowDroneInfoDynamicInt: public JsonBase {
public: 
    /** 电池剩余电量百分比 */
    int32_t bat;
    /** 燃油剩余量百分比,或燃油数量,升 */
    int32_t fuel;
    /** 是否携带摄像头, 摄像头可能动态加载. 0:无摄像头, 1: 有摄像头 */
    int32_t cam;
    /** 马达是否启动. 0:未启动, 1:已启动 */
    int32_t arm;
    /** 是否已起飞到空中, 0: 在地上, 1: 在空中 */
    int32_t air;
    /** 电池电压, 实际值*100 */
    int vol;
    /** 当前绝对速度, 米/秒, 实际值*100 */
    int absp;
    /** 环境温度,摄氏度, 实际值*100 */
    int temp;
    /** 最大飞行速度, 米/秒 */
    int maxSpd;
    /** 返航爬升高度 */
    int retHt;
    /** 飞行任务完成后是否自动返航, 0: 不自动返航, 1: 自动返航 */
    int autoRet;
    /** 是否处于离线模式, 0:非离线模式, 1: 离线模式 */
    int offboard;
    /** 总航点数量 */
    int32_t total;
    /** 当前目标航点索引[0,total], 0表示启动飞行器出发 */
    int32_t curr;
    /** 执行是否完成 */
    int32_t over;
    /** 循环执行次数 */
    int32_t loop;
    /** 当前循环索引 */
    int32_t lpidx;
    /** 当前位置到下一个航点的距离, 单位米 */
    int dis;
    /** 当前飞行模式 */
    string mode;
    /** 当前故障码, trouble code */
    string tc;
    /** 活动类型：land-降落/track-轨迹记录 */
    string act;
    /** 针对复亚机场新增, 当前航线编号,两字节整型 */
    int32_t rid;
    /** 针对复亚机场新增, 当前是否开启直播录像 */
    int32_t recording;
    /** 针对复亚机场新增, 已拍摄照片数量 */
    int32_t snapNum;
    /** 针对复亚机场新增, 航线完成百分比 */
    int32_t routeRatio;
    /** 针对复亚机场新增, 云台相机的角度 */
    FuyaGimbal *gimbal = NULL;
    /** 针对复亚机场新增, 错误码,两字节整型, 16bit, 每个bit代表一种错误信息 */
    int32_t errcode;
    /** 适配复亚机场，00=不会自动发送  01=n hz  02=更新才发送 */
    int32_t autoUpdate;
    /** 针对复亚机场新增, 是否落地入库, 整型 */
    int32_t backhome;
    /** gps卫星数量 */
    int gpsSatNum;
    /** gps信号质量, 0~5 */
    int gpsLevel;
    /** 已飞行时长, 单位秒 */
    int flyTime;
    /** 飞行器头部当前方位 */
    int hdir;
    /** 遥控器与飞机之间的信号质量, 1~100 */
    int siglev = 0;
    /** 地面站位置 */
    LngLatHgtAltInt *spos = NULL;
    /** SDK类型 */
    string sdk;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneInfoDynamicInt* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("bat")) {
            bat = jsonObj["bat"];
        }
        if(jsonObj.contains("fuel")) {
            fuel = jsonObj["fuel"];
        }
        if(jsonObj.contains("cam")) {
            cam = jsonObj["cam"];
        }
        if(jsonObj.contains("arm")) {
            arm = jsonObj["arm"];
        }
        if(jsonObj.contains("air")) {
            air = jsonObj["air"];
        }
        if(jsonObj.contains("vol")) {
            vol = jsonObj["vol"];
        }
        if(jsonObj.contains("absp")) {
            absp = jsonObj["absp"];
        }
        if(jsonObj.contains("temp")) {
            temp = jsonObj["temp"];
        }
        if(jsonObj.contains("maxSpd")) {
            maxSpd = jsonObj["maxSpd"];
        }
        if(jsonObj.contains("retHt")) {
            retHt = jsonObj["retHt"];
        }
        if(jsonObj.contains("autoRet")) {
            autoRet = jsonObj["autoRet"];
        }
        if(jsonObj.contains("offboard")) {
            offboard = jsonObj["offboard"];
        }
        if(jsonObj.contains("total")) {
            total = jsonObj["total"];
        }
        if(jsonObj.contains("curr")) {
            curr = jsonObj["curr"];
        }
        if(jsonObj.contains("over")) {
            over = jsonObj["over"];
        }
        if(jsonObj.contains("loop")) {
            loop = jsonObj["loop"];
        }
        if(jsonObj.contains("lpidx")) {
            lpidx = jsonObj["lpidx"];
        }
        if(jsonObj.contains("dis")) {
            dis = jsonObj["dis"];
        }
        if(jsonObj.contains("mode")) {
            mode = jsonObj["mode"];
        }
        if(jsonObj.contains("tc")) {
            tc = jsonObj["tc"];
        }
        if(jsonObj.contains("act")) {
            act = jsonObj["act"];
        }
        if(jsonObj.contains("rid")) {
            rid = jsonObj["rid"];
        }
        if(jsonObj.contains("recording")) {
            recording = jsonObj["recording"];
        }
        if(jsonObj.contains("snapNum")) {
            snapNum = jsonObj["snapNum"];
        }
        if(jsonObj.contains("routeRatio")) {
            routeRatio = jsonObj["routeRatio"];
        }
        if(jsonObj.contains("gimbal")) {
            gimbal = new FuyaGimbal();
            gimbal->parseFromJson(jsonObj["gimbal"]);
        }
        if(jsonObj.contains("errcode")) {
            errcode = jsonObj["errcode"];
        }
        if(jsonObj.contains("autoUpdate")) {
            autoUpdate = jsonObj["autoUpdate"];
        }
        if(jsonObj.contains("backhome")) {
            backhome = jsonObj["backhome"];
        }
        if(jsonObj.contains("gpsSatNum")) {
            gpsSatNum = jsonObj["gpsSatNum"];
        }
        if(jsonObj.contains("gpsLevel")) {
            gpsLevel = jsonObj["gpsLevel"];
        }
        if(jsonObj.contains("flyTime")) {
            flyTime = jsonObj["flyTime"];
        }
        if(jsonObj.contains("hdir")) {
            hdir = jsonObj["hdir"];
        }
        if(jsonObj.contains("siglev")) {
            siglev = jsonObj["siglev"];
        }
        if(jsonObj.contains("spos")) {
            spos = new LngLatHgtAltInt();
            spos->parseFromJson(jsonObj["spos"]);
        }
        if(jsonObj.contains("sdk")) {
            sdk = jsonObj["sdk"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["bat"] = bat;
        jsonObj["fuel"] = fuel;
        jsonObj["cam"] = cam;
        jsonObj["arm"] = arm;
        jsonObj["air"] = air;
        jsonObj["vol"] = vol;
        jsonObj["absp"] = absp;
        jsonObj["temp"] = temp;
        jsonObj["maxSpd"] = maxSpd;
        jsonObj["retHt"] = retHt;
        jsonObj["autoRet"] = autoRet;
        jsonObj["offboard"] = offboard;
        jsonObj["total"] = total;
        jsonObj["curr"] = curr;
        jsonObj["over"] = over;
        jsonObj["loop"] = loop;
        jsonObj["lpidx"] = lpidx;
        jsonObj["dis"] = dis;
        if(!mode.empty()) {
            jsonObj["mode"] = mode;
        }
        if(!tc.empty()) {
            jsonObj["tc"] = tc;
        }
        if(!act.empty()) {
            jsonObj["act"] = act;
        }
        jsonObj["rid"] = rid;
        jsonObj["recording"] = recording;
        jsonObj["snapNum"] = snapNum;
        jsonObj["routeRatio"] = routeRatio;
        if(gimbal) {
            json subJsonOfGimbal;
            gimbal->toJson(subJsonOfGimbal);
            jsonObj["gimbal"] = subJsonOfGimbal;
        }
        jsonObj["errcode"] = errcode;
        jsonObj["autoUpdate"] = autoUpdate;
        jsonObj["backhome"] = backhome;
        jsonObj["gpsSatNum"] = gpsSatNum;
        jsonObj["gpsLevel"] = gpsLevel;
        jsonObj["flyTime"] = flyTime;
        jsonObj["hdir"] = hdir;
        jsonObj["siglev"] = siglev;
        if(spos) {
            json subJsonOfSpos;
            spos->toJson(subJsonOfSpos);
            jsonObj["spos"] = subJsonOfSpos;
        }
        if(!sdk.empty()) {
            jsonObj["sdk"] = sdk;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneInfoDynamicInt 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["bat"] = bat;
        jsonObj["fuel"] = fuel;
        jsonObj["cam"] = cam;
        jsonObj["arm"] = arm;
        jsonObj["air"] = air;
        jsonObj["vol"] = vol;
        jsonObj["absp"] = absp;
        jsonObj["temp"] = temp;
        jsonObj["maxSpd"] = maxSpd;
        jsonObj["retHt"] = retHt;
        jsonObj["autoRet"] = autoRet;
        jsonObj["offboard"] = offboard;
        jsonObj["total"] = total;
        jsonObj["curr"] = curr;
        jsonObj["over"] = over;
        jsonObj["loop"] = loop;
        jsonObj["lpidx"] = lpidx;
        jsonObj["dis"] = dis;
        if(!mode.empty()) {
            jsonObj["mode"] = mode;
        }
        if(!tc.empty()) {
            jsonObj["tc"] = tc;
        }
        if(!act.empty()) {
            jsonObj["act"] = act;
        }
        jsonObj["rid"] = rid;
        jsonObj["recording"] = recording;
        jsonObj["snapNum"] = snapNum;
        jsonObj["routeRatio"] = routeRatio;
        if(gimbal) {
            json subJsonOfGimbal;
            gimbal->toJson(subJsonOfGimbal);
            jsonObj["gimbal"] = subJsonOfGimbal;
        }
        jsonObj["errcode"] = errcode;
        jsonObj["autoUpdate"] = autoUpdate;
        jsonObj["backhome"] = backhome;
        jsonObj["gpsSatNum"] = gpsSatNum;
        jsonObj["gpsLevel"] = gpsLevel;
        jsonObj["flyTime"] = flyTime;
        jsonObj["hdir"] = hdir;
        jsonObj["siglev"] = siglev;
        if(spos) {
            json subJsonOfSpos;
            spos->toJson(subJsonOfSpos);
            jsonObj["spos"] = subJsonOfSpos;
        }
        if(!sdk.empty()) {
            jsonObj["sdk"] = sdk;
        }

        return;
    }
public:
    FcowDroneInfoDynamicInt() {
        bat = 0;
        fuel = 0;
        cam = 0;
        arm = 0;
        air = 0;
        vol = 0;
        absp = 0;
        temp = 0;
        maxSpd = 0;
        retHt = 0;
        autoRet = 0;
        offboard = 0;
        total = 0;
        curr = 0;
        over = 0;
        loop = 0;
        lpidx = 0;
        dis = 0;
        rid = 0;
        recording = 0;
        snapNum = 0;
        routeRatio = 0;
        errcode = 0;
        autoUpdate = 0;
        backhome = 0;
        gpsSatNum = 0;
        gpsLevel = 0;
        flyTime = 0;
        hdir = 0;
    }
    virtual ~FcowDroneInfoDynamicInt() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(gimbal) {
            delete gimbal;
        }
        //对象类型指针约定使用new初始化, delete释放
        if(spos) {
            delete spos;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 设备位置.
将经纬度放在前面,适应mongodb数据库地理位置查询.
*/
class  FcowDronePoint: public JsonBase {
public: 
    /** 经度 */
    double lng;
    /** 纬度 */
    double lat;
    /** 离地高度, 实际为距离起飞点的相对高度 */
    float ht;
    /** 海拔高度 */
    float alt;
    /** 地速（单位：米/秒，精确到小数点后2位）*/
    float spd;
    /** 真航向（单位：度，取值范围:[0,360]，精确到小数点后1位. 正北为0,顺时针递增） */
    float head;
    /** 俯仰角（单位: 度，取值范围:[-90,90], 精确到小数点后1位，仰为正，俯为负） */
    float pit;
    /** 横滚角（单位：度，精确到小数点后1位，向左为正，向右为负） */
    float roll;
    /** 采集时间（北京时间戳，精确到豪秒, 64位整型） */
    int64_t time;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDronePoint* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lng")) {
            lng = jsonObj["lng"];
        }
        if(jsonObj.contains("lat")) {
            lat = jsonObj["lat"];
        }
        if(jsonObj.contains("ht")) {
            ht = jsonObj["ht"];
        }
        if(jsonObj.contains("alt")) {
            alt = jsonObj["alt"];
        }
        if(jsonObj.contains("spd")) {
            spd = jsonObj["spd"];
        }
        if(jsonObj.contains("head")) {
            head = jsonObj["head"];
        }
        if(jsonObj.contains("pit")) {
            pit = jsonObj["pit"];
        }
        if(jsonObj.contains("roll")) {
            roll = jsonObj["roll"];
        }
        if(jsonObj.contains("time")) {
            time = jsonObj["time"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;
        jsonObj["spd"] = spd;
        jsonObj["head"] = head;
        jsonObj["pit"] = pit;
        jsonObj["roll"] = roll;
        jsonObj["time"] = time;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDronePoint 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;
        jsonObj["spd"] = spd;
        jsonObj["head"] = head;
        jsonObj["pit"] = pit;
        jsonObj["roll"] = roll;
        jsonObj["time"] = time;

        return;
    }
public:
    FcowDronePoint() {
        lng = 0;
        lat = 0;
        ht = 0;
        alt = 0;
        spd = 0;
        head = 0;
        pit = 0;
        roll = 0;
        time = 0;
    }
    virtual ~FcowDronePoint() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 设备位置.
将经纬度放在前面,适应mongodb数据库地理位置查询.
用于数据库精度测试
*/
class FcowDronePointInt: public JsonBase {
public: 
    /** 经度, 实际值*10000000 */
    int lng;
    /** 纬度, 实际值*10000000 */
    int lat;
    /** 离地高度, 实际为距离起飞点的相对高度, 实际值*100 */
    int ht;
    /** 海拔高度, 实际值*100 */
    int alt;
    /** 地速（单位：米/秒，精确到小数点后2位）, 实际值*100*/
    int spd;
    /** 真航向（单位：度，取值范围:[0,360]，精确到小数点后1位. 正北为0,顺时针递增）, 实际值*100 */
    int head;
    /** 俯仰角（单位: 度，取值范围:[-90,90], 精确到小数点后1位，仰为正，俯为负）, 实际值*100 */
    int pit;
    /** 横滚角（单位：度，精确到小数点后1位，向左为正，向右为负）, 实际值*100 */
    int roll;
    /** 采集时间（北京时间戳，精确到豪秒, 64位整型） */
    int64_t time;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDronePointInt* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lng")) {
            lng = jsonObj["lng"];
        }
        if(jsonObj.contains("lat")) {
            lat = jsonObj["lat"];
        }
        if(jsonObj.contains("ht")) {
            ht = jsonObj["ht"];
        }
        if(jsonObj.contains("alt")) {
            alt = jsonObj["alt"];
        }
        if(jsonObj.contains("spd")) {
            spd = jsonObj["spd"];
        }
        if(jsonObj.contains("head")) {
            head = jsonObj["head"];
        }
        if(jsonObj.contains("pit")) {
            pit = jsonObj["pit"];
        }
        if(jsonObj.contains("roll")) {
            roll = jsonObj["roll"];
        }
        if(jsonObj.contains("time")) {
            time = jsonObj["time"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;
        jsonObj["spd"] = spd;
        jsonObj["head"] = head;
        jsonObj["pit"] = pit;
        jsonObj["roll"] = roll;
        jsonObj["time"] = time;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDronePointInt 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;
        jsonObj["spd"] = spd;
        jsonObj["head"] = head;
        jsonObj["pit"] = pit;
        jsonObj["roll"] = roll;
        jsonObj["time"] = time;

        return;
    }
public:
    FcowDronePointInt() {
        lng = 0;
        lat = 0;
        ht = 0;
        alt = 0;
        spd = 0;
        head = 0;
        pit = 0;
        roll = 0;
        time = 0;
    }
    virtual ~FcowDronePointInt() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/** 通用的设备端消息反馈 */
class FcowDroneFeedback: public JsonBase {
public: 
    /** 头信息 */
    FcowHead *head = NULL;
    /** 设备注册号, 设备端的回复信息需附带该字段 */
    string regno;
    /** 状态值. 0->处理失败, 由msg给出原因; 1->处理成功 */
    int32_t state;
    /** 处理失败原因 */
    map<string,string> *data = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneFeedback* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head = new FcowHead();
            head->parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("state")) {
            state = jsonObj["state"];
        }
        if(jsonObj.contains("data")) {
            data = new map<string,string>();
            for (auto& item : jsonObj["data"].items()){
                string key = item.key();
                string value = item.value();
                data->insert(pair<string,string>(key, value));
            }

        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(head) {
            json subJsonOfHead;
            head->toJson(subJsonOfHead);
            jsonObj["head"] = subJsonOfHead;
        }
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["state"] = state;
        if(data) {
            for(auto &it : *data) {
                string key = it.first;
                string value = it.second;
                jsonObj["data"][key] = value;
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneFeedback 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(head) {
            json subJsonOfHead;
            head->toJson(subJsonOfHead);
            jsonObj["head"] = subJsonOfHead;
        }
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["state"] = state;
        if(data) {
            for(auto &it : *data) {
                string key = it.first;
                string value = it.second;
                jsonObj["data"][key] = value;
            }
        }

        return;
    }
public:
    FcowDroneFeedback() {
        state = 0;
    }
    virtual ~FcowDroneFeedback() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(head) {
            delete head;
        }
        if(data) {
            //对象类型指针约定使用new初始化, delete释放
            delete data;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 通用的平台端消息反馈 */
class FcowServerFeedback: public JsonBase {
public: 
    /** 头信息 */
    FcowHead *head = NULL;
    /** 状态值. 0->处理失败, 由msg给出原因; 1->处理成功 */
    int32_t state;
    /** 处理失败原因 */
    map<string,string> *data = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowServerFeedback* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head = new FcowHead();
            head->parseFromJson(jsonObj["head"]);
        }
        if(jsonObj.contains("state")) {
            state = jsonObj["state"];
        }
        if(jsonObj.contains("data")) {
            data = new map<string,string>();
            for (auto& item : jsonObj["data"].items()){
                string key = item.key();
                string value = item.value();
                data->insert(pair<string,string>(key, value));
            }

        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(head) {
            json subJsonOfHead;
            head->toJson(subJsonOfHead);
            jsonObj["head"] = subJsonOfHead;
        }
        jsonObj["state"] = state;
        if(data) {
            for(auto &it : *data) {
                string key = it.first;
                string value = it.second;
                jsonObj["data"][key] = value;
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowServerFeedback 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(head) {
            json subJsonOfHead;
            head->toJson(subJsonOfHead);
            jsonObj["head"] = subJsonOfHead;
        }
        jsonObj["state"] = state;
        if(data) {
            for(auto &it : *data) {
                string key = it.first;
                string value = it.second;
                jsonObj["data"][key] = value;
            }
        }

        return;
    }
public:
    FcowServerFeedback() {
        state = 0;
    }
    virtual ~FcowServerFeedback() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(head) {
            delete head;
        }
        if(data) {
            //对象类型指针约定使用new初始化, delete释放
            delete data;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 预置位 */
class CameraPreset: public JsonBase {
public: 
    /** 预置位编号 */
    int idx;
    /** 预置位名称 */
    string name;
    /** 所属航点编号 */
    int fpidx;
    /** 所属航点名称 */
    string fpname;
    /** 水平方位, 单位:度 */
    float yaw;
    /** 俯仰角, 单位:度 */
    float pitch;
    /** 焦距, 单位:度 */
    float focus;
    /** 截图数量, 默认不截图 */
    int snapNum=0;
    /** 截图时间间隔, 默认3秒 */
    int snapItv=3;
    /** 确认结果, 0: 未确认, 1: 无异常, 2: 疑似异常, 3: 确认异常, 4: 确认误报 */
    int resState=0;
    /** 结果处理描述 */
    string resMemo;
    string xjdId;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual CameraPreset* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("idx")) {
            idx = jsonObj["idx"];
        }
        if(jsonObj.contains("name")) {
            name = jsonObj["name"];
        }
        if(jsonObj.contains("fpidx")) {
            fpidx = jsonObj["fpidx"];
        }
        if(jsonObj.contains("fpname")) {
            fpname = jsonObj["fpname"];
        }
        if(jsonObj.contains("yaw")) {
            yaw = jsonObj["yaw"];
        }
        if(jsonObj.contains("pitch")) {
            pitch = jsonObj["pitch"];
        }
        if(jsonObj.contains("focus")) {
            focus = jsonObj["focus"];
        }
        if(jsonObj.contains("snapNum")) {
            snapNum = jsonObj["snapNum"];
        }
        if(jsonObj.contains("snapItv")) {
            snapItv = jsonObj["snapItv"];
        }
        if(jsonObj.contains("resState")) {
            resState = jsonObj["resState"];
        }
        if(jsonObj.contains("resMemo")) {
            resMemo = jsonObj["resMemo"];
        }
        if(jsonObj.contains("xjdId")) {
            xjdId = jsonObj["xjdId"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["idx"] = idx;
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        jsonObj["fpidx"] = fpidx;
        if(!fpname.empty()) {
            jsonObj["fpname"] = fpname;
        }
        jsonObj["yaw"] = yaw;
        jsonObj["pitch"] = pitch;
        jsonObj["focus"] = focus;
        jsonObj["snapNum"] = snapNum;
        jsonObj["snapItv"] = snapItv;
        jsonObj["resState"] = resState;
        if(!resMemo.empty()) {
            jsonObj["resMemo"] = resMemo;
        }
        if(!xjdId.empty()) {
            jsonObj["xjdId"] = xjdId;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("CameraPreset 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["idx"] = idx;
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        jsonObj["fpidx"] = fpidx;
        if(!fpname.empty()) {
            jsonObj["fpname"] = fpname;
        }
        jsonObj["yaw"] = yaw;
        jsonObj["pitch"] = pitch;
        jsonObj["focus"] = focus;
        jsonObj["snapNum"] = snapNum;
        jsonObj["snapItv"] = snapItv;
        jsonObj["resState"] = resState;
        if(!resMemo.empty()) {
            jsonObj["resMemo"] = resMemo;
        }
        if(!xjdId.empty()) {
            jsonObj["xjdId"] = xjdId;
        }

        return;
    }
public:
    CameraPreset() {
        idx = 0;
        fpidx = 0;
        yaw = 0;
        pitch = 0;
        focus = 0;
    }
    virtual ~CameraPreset() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/**
航线飞行位置点.
将经纬度放在前面,适应mongodb数据库地理位置查询
*/
class FlyPoint : public JsonBase {
public: 
    /** 航点编号, 从0开始 */
    int32_t idx;
    /** 航点名称 */
    string name;
    /** 经度 */
    double lng;
    /** 纬度 */
    double lat;
    /** 离地高度或相对高度, m */
    float ht = 0;
    /** 海拔高度, m */
    float alt = 0;
    /** 速度, m/s */
    float spd = 3;
    /** 半径, m */
    int32_t radius = 0;
    /** 悬停时间, 单位:秒 */
    int32_t hov = 0;
    /** 悬停速度, m/s */
    float hspd = 0;
    /** 可选, 水平航向. 正北为0,顺时针递增 */
    float head = 0;
    /** 是否必须飞经该点, 默认不限制 */
    int32_t flyThr = 0;
    /** 云台方向角, 适配复亚机场 */
    int32_t gimyaw;
    /** 云台俯仰角, 适配复亚机场 */
    int32_t gimpitch;
    /** 拐弯半径, 适配复亚机场 */
    int32_t tr;
    /** 可选项, 相机动作, 0->无动作,1->截图一张,2->开始截图,3->停止截图,4->开始录像,5->停止录像 */
    int32_t action = 0;
    /** 兼容qgc格式, 是否自动继续, 如果不继续表示悬停, 默认为true */
    int32_t autoCon = 1;
    /** 兼容qgc格式, mavlink命令, 22->起飞, 21->降落, 20->返航, 19->盘旋指定时间(秒), 16->正常经过, 默认为16 */
    int32_t cmd = 16;
    /** 预置位列表 */
    vector<CameraPreset*> *presets = NULL;
    /** 悬停时是否录像 */
    int recordOnHov=0;
    /** 预置位间隔时间, 单位:秒 */
    int presetItv=3;
    string towerId;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FlyPoint* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("idx")) {
            idx = jsonObj["idx"];
        }
        if(jsonObj.contains("name")) {
            name = jsonObj["name"];
        }
        if(jsonObj.contains("lng")) {
            lng = jsonObj["lng"];
        }
        if(jsonObj.contains("lat")) {
            lat = jsonObj["lat"];
        }
        if(jsonObj.contains("ht")) {
            ht = jsonObj["ht"];
        }
        if(jsonObj.contains("alt")) {
            alt = jsonObj["alt"];
        }
        if(jsonObj.contains("spd")) {
            spd = jsonObj["spd"];
        }
        if(jsonObj.contains("radius")) {
            radius = jsonObj["radius"];
        }
        if(jsonObj.contains("hov")) {
            hov = jsonObj["hov"];
        }
        if(jsonObj.contains("hspd")) {
            hspd = jsonObj["hspd"];
        }
        if(jsonObj.contains("head")) {
            head = jsonObj["head"];
        }
        if(jsonObj.contains("flyThr")) {
            flyThr = jsonObj["flyThr"];
        }
        if(jsonObj.contains("gimyaw")) {
            gimyaw = jsonObj["gimyaw"];
        }
        if(jsonObj.contains("gimpitch")) {
            gimpitch = jsonObj["gimpitch"];
        }
        if(jsonObj.contains("tr")) {
            tr = jsonObj["tr"];
        }
        if(jsonObj.contains("action")) {
            action = jsonObj["action"];
        }
        if(jsonObj.contains("autoCon")) {
            autoCon = jsonObj["autoCon"];
        }
        if(jsonObj.contains("cmd")) {
            cmd = jsonObj["cmd"];
        }
        if(jsonObj.contains("presets")) {
            presets = new vector<CameraPreset*>();
            for (auto& listItem : jsonObj["presets"].items()){
                CameraPreset *vinst = new CameraPreset();
                vinst->parseFromJson(listItem.value());
                presets->push_back(vinst);
            }
        }
        if(jsonObj.contains("recordOnHov")) {
            recordOnHov = jsonObj["recordOnHov"];
        }
        if(jsonObj.contains("presetItv")) {
            presetItv = jsonObj["presetItv"];
        }
        if(jsonObj.contains("towerId")) {
            towerId = jsonObj["towerId"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["idx"] = idx;
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;
        jsonObj["spd"] = spd;
        jsonObj["radius"] = radius;
        jsonObj["hov"] = hov;
        jsonObj["hspd"] = hspd;
        jsonObj["head"] = head;
        jsonObj["flyThr"] = flyThr;
        jsonObj["gimyaw"] = gimyaw;
        jsonObj["gimpitch"] = gimpitch;
        jsonObj["tr"] = tr;
        jsonObj["action"] = action;
        jsonObj["autoCon"] = autoCon;
        jsonObj["cmd"] = cmd;
        if(presets) {
            for(auto &it : *presets) {
                json subJsonOfIt2108;
                it->toJson(subJsonOfIt2108);
                jsonObj["presets"].push_back(subJsonOfIt2108);
            }
        }
        jsonObj["recordOnHov"] = recordOnHov;
        jsonObj["presetItv"] = presetItv;
        if(!towerId.empty()) {
            jsonObj["towerId"] = towerId;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FlyPoint 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["idx"] = idx;
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;
        jsonObj["spd"] = spd;
        jsonObj["radius"] = radius;
        jsonObj["hov"] = hov;
        jsonObj["hspd"] = hspd;
        jsonObj["head"] = head;
        jsonObj["flyThr"] = flyThr;
        jsonObj["gimyaw"] = gimyaw;
        jsonObj["gimpitch"] = gimpitch;
        jsonObj["tr"] = tr;
        jsonObj["action"] = action;
        jsonObj["autoCon"] = autoCon;
        jsonObj["cmd"] = cmd;
        if(presets) {
            for(auto &it : *presets) {
                json subJsonOfIt518;
                it->toJson(subJsonOfIt518);
                jsonObj["presets"].push_back(subJsonOfIt518);
            }
        }
        jsonObj["recordOnHov"] = recordOnHov;
        jsonObj["presetItv"] = presetItv;
        if(!towerId.empty()) {
            jsonObj["towerId"] = towerId;
        }

        return;
    }
public:
    FlyPoint() {
        idx = 0;
        lng = 0;
        lat = 0;
        gimyaw = 0;
        gimpitch = 0;
        tr = 0;
    }
    virtual ~FlyPoint() {
        // 开始释放对象 
        if(presets) {
            for(auto &it : *presets) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete presets;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/**
简化版的航线对象, 属于Route.FlyRoute的子集
*/
class FcowDroneRoute : public JsonBase {
public: 
    /** 航点列表 */
    vector<FlyPoint*> *pts = NULL;
    /** 标志id */
    string id;
    /** 航线名称, 可选项 */
    string name;
    int32_t sn;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneRoute* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("pts")) {
            pts = new vector<FlyPoint*>();
            for (auto& listItem : jsonObj["pts"].items()){
                FlyPoint *vinst = new FlyPoint();
                vinst->parseFromJson(listItem.value());
                pts->push_back(vinst);
            }
        }
        if(jsonObj.contains("id")) {
            id = jsonObj["id"];
        }
        if(jsonObj.contains("name")) {
            name = jsonObj["name"];
        }
        if(jsonObj.contains("sn")) {
            sn = jsonObj["sn"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(pts) {
            for(auto &it : *pts) {
                json subJsonOfIt9181;
                it->toJson(subJsonOfIt9181);
                jsonObj["pts"].push_back(subJsonOfIt9181);
            }
        }
        if(!id.empty()) {
            jsonObj["id"] = id;
        }
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        jsonObj["sn"] = sn;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneRoute 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(pts) {
            for(auto &it : *pts) {
                json subJsonOfIt690;
                it->toJson(subJsonOfIt690);
                jsonObj["pts"].push_back(subJsonOfIt690);
            }
        }
        if(!id.empty()) {
            jsonObj["id"] = id;
        }
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        jsonObj["sn"] = sn;

        return;
    }
public:
    FcowDroneRoute() {
        sn = 0;
    }
    virtual ~FcowDroneRoute() {
        // 开始释放对象 
        if(pts) {
            for(auto &it : *pts) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete pts;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 航线执行进度内容 */
class FcowDroneRouteProgress: public JsonBase {
public: 
    /** 总航点数量 */
    int32_t total;
    /** 当前目标航点索引[0,total], 0表示启动飞行器出发 */
    int32_t curr;
    /** 执行是否完成 */
    int32_t over;
    /** 航线id */
    string routeId;
    /** [该字段暂未使用] 是否是预置位到达事件, 0:表示当前进度事件是航点到达事件; 1:表示为预置位达到事件, 航点不变. */
    int32_t isPreset=0;
    /** [该字段暂未使用] 预置位编号 */
    int32_t presetIdx;
    /** 如果执行失败, 即over = 1但是curr! = total, 这里尝试给出原因 */
    string msg;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual FcowDroneRouteProgress* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("total")) {
            total = jsonObj["total"];
        }
        if(jsonObj.contains("curr")) {
            curr = jsonObj["curr"];
        }
        if(jsonObj.contains("over")) {
            over = jsonObj["over"];
        }
        if(jsonObj.contains("routeId")) {
            routeId = jsonObj["routeId"];
        }
        if(jsonObj.contains("isPreset")) {
            isPreset = jsonObj["isPreset"];
        }
        if(jsonObj.contains("presetIdx")) {
            presetIdx = jsonObj["presetIdx"];
        }
        if(jsonObj.contains("msg")) {
            msg = jsonObj["msg"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["total"] = total;
        jsonObj["curr"] = curr;
        jsonObj["over"] = over;
        if(!routeId.empty()) {
            jsonObj["routeId"] = routeId;
        }
        jsonObj["isPreset"] = isPreset;
        jsonObj["presetIdx"] = presetIdx;
        if(!msg.empty()) {
            jsonObj["msg"] = msg;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("FcowDroneRouteProgress 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["total"] = total;
        jsonObj["curr"] = curr;
        jsonObj["over"] = over;
        if(!routeId.empty()) {
            jsonObj["routeId"] = routeId;
        }
        jsonObj["isPreset"] = isPreset;
        jsonObj["presetIdx"] = presetIdx;
        if(!msg.empty()) {
            jsonObj["msg"] = msg;
        }

        return;
    }
public:
    FcowDroneRouteProgress() {
        total = 0;
        curr = 0;
        over = 0;
        presetIdx = 0;
    }
    virtual ~FcowDroneRouteProgress() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/**
简化版的目标检测结果
*/
class TargetPara : public JsonBase {
public: 
    /** 设备标识 */
    string regno;
    /** 检测时间戳 */
    int64_t time;
    /** 相对飞行器位置距离，单位km 实际值乘以100 */
    double dis;
    /** 相对飞行器位置夹角，单位度 相对飞行器运行方向的顺时针为正 [0.360) ,实际值乘以100*/
    float head;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual TargetPara* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        if(jsonObj.contains("time")) {
            time = jsonObj["time"];
        }
        if(jsonObj.contains("dis")) {
            dis = jsonObj["dis"];
        }
        if(jsonObj.contains("head")) {
            head = jsonObj["head"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["time"] = time;
        jsonObj["dis"] = dis;
        jsonObj["head"] = head;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("TargetPara 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }
        jsonObj["time"] = time;
        jsonObj["dis"] = dis;
        jsonObj["head"] = head;

        return;
    }
public:
    TargetPara() {
        time = 0;
        dis = 0;
        head = 0;
    }
    virtual ~TargetPara() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

} 
