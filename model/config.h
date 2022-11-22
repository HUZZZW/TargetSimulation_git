/*******************************************************************************
 * 版权所有 2017-2018 www.fcow-it.com
 * 构建时间: 2022-03-09
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


//nlohmann/json
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

namespace schedule {
/**
通用基础数据类定义, 雷达仿真软件配置参数相关
2022-03-09 ，mqzhao
*/



/** 配置文件类 */
class ConfigInfo: public JsonBase {
public: 
    /** 本地监听端口 暂定  */
    int32_t port;
    /** 组播地址 未启用  */
    string address;
    /** 通信类型  0:UDP  1:其他 暂时仅支持udp模式 */
    int32_t type;
    /** 红外图像生成软件的遥控地址  */
    string osg_address;
    /** 红外图像生成软件的遥控端口  */
    int32_t osg_port;
    /** 是否向红外图像生成软件转发第三方的遥控指令  */
    int32_t osg_enable;
    /** 雷达图像生成软件的遥控地址  */
    string radargui_address;
    /** 雷达图像生成软件的遥控端口  */
    int32_t radargui_port;
    /** 是否向雷达图像生成软件转发第三方的遥控指令  */
    int32_t radargui_enable;
    /** 第三方软件的遥测地址  */
    string thrid_address;
    /** 第三方软件的遥测端口  */
    int32_t thrid_port;
    /** 是否向第三方软件转发雷达状态数据  */
    int32_t third_enable;
    /** 遥测指令转发频率，单位毫秒ms  */
    int32_t interval;
    /** 当前雷达设备绑定的飞行器唯一性ID  */
    string plane_regno;
    /** 当前雷达设备唯一性ID  */
    string regno;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual ConfigInfo* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("port")) {
            port = jsonObj["port"];
        }
        if(jsonObj.contains("address")) {
            address = jsonObj["address"];
        }
        if(jsonObj.contains("type")) {
            type = jsonObj["type"];
        }
        if(jsonObj.contains("osg_address")) {
            osg_address = jsonObj["osg_address"];
        }
        if(jsonObj.contains("osg_port")) {
            osg_port = jsonObj["osg_port"];
        }
        if(jsonObj.contains("osg_enable")) {
            osg_enable = jsonObj["osg_enable"];
        }
        if(jsonObj.contains("radargui_address")) {
            radargui_address = jsonObj["radargui_address"];
        }
        if(jsonObj.contains("radargui_port")) {
            radargui_port = jsonObj["radargui_port"];
        }
        if(jsonObj.contains("radargui_enable")) {
            radargui_enable = jsonObj["radargui_enable"];
        }
        if(jsonObj.contains("thrid_address")) {
            thrid_address = jsonObj["thrid_address"];
        }
        if(jsonObj.contains("thrid_port")) {
            thrid_port = jsonObj["thrid_port"];
        }
        if(jsonObj.contains("third_enable")) {
            third_enable = jsonObj["third_enable"];
        }
        if(jsonObj.contains("interval")) {
            interval = jsonObj["interval"];
        }
        if(jsonObj.contains("plane_regno")) {
            plane_regno = jsonObj["plane_regno"];
        }
        if(jsonObj.contains("regno")) {
            regno = jsonObj["regno"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["port"] = port;
        if(!address.empty()) {
            jsonObj["address"] = address;
        }
        jsonObj["type"] = type;
        if(!osg_address.empty()) {
            jsonObj["osg_address"] = osg_address;
        }
        jsonObj["osg_port"] = osg_port;
        jsonObj["osg_enable"] = osg_enable;
        if(!radargui_address.empty()) {
            jsonObj["radargui_address"] = radargui_address;
        }
        jsonObj["radargui_port"] = radargui_port;
        jsonObj["radargui_enable"] = radargui_enable;
        if(!thrid_address.empty()) {
            jsonObj["thrid_address"] = thrid_address;
        }
        jsonObj["thrid_port"] = thrid_port;
        jsonObj["third_enable"] = third_enable;
        jsonObj["interval"] = interval;
        if(!plane_regno.empty()) {
            jsonObj["plane_regno"] = plane_regno;
        }
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("ConfigInfo 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["port"] = port;
        if(!address.empty()) {
            jsonObj["address"] = address;
        }
        jsonObj["type"] = type;
        if(!osg_address.empty()) {
            jsonObj["osg_address"] = osg_address;
        }
        jsonObj["osg_port"] = osg_port;
        jsonObj["osg_enable"] = osg_enable;
        if(!radargui_address.empty()) {
            jsonObj["radargui_address"] = radargui_address;
        }
        jsonObj["radargui_port"] = radargui_port;
        jsonObj["radargui_enable"] = radargui_enable;
        if(!thrid_address.empty()) {
            jsonObj["thrid_address"] = thrid_address;
        }
        jsonObj["thrid_port"] = thrid_port;
        jsonObj["third_enable"] = third_enable;
        jsonObj["interval"] = interval;
        if(!plane_regno.empty()) {
            jsonObj["plane_regno"] = plane_regno;
        }
        if(!regno.empty()) {
            jsonObj["regno"] = regno;
        }

        return;
    }
public:
    ConfigInfo() {
        port = 0;
        type = 0;
        osg_port = 0;
        osg_enable = 0;
        radargui_port = 0;
        radargui_enable = 0;
        thrid_port = 0;
        third_enable = 0;
        interval = 0;
    }
    virtual ~ConfigInfo() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

} 
