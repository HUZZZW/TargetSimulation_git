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

namespace schedule {
/**
通用基础数据类定义
2022-03-10, mqzhao
*/


/**
* 运营商CPN编号, 3个字符, 从001开始
*/
const int32_t OPERATOR_CPN_BASE = 999;

/**
* 最小经度
*/
const double MIN_LONGITUDE = -180;

/**
* 最大经度
*/
const double MAX_LONGITUDE = 180;
/**
* 最小纬度
*/
const double MIN_LATITUDE = -90;

/**
* 最大纬度
*/
const double MAX_LATITUDE = 90;

/**
经纬度坐标系, 地球坐标WGS84, 默认GPS坐标系.
国际标准，从专业GPS 设备中取出的数据的坐标系;
WGS-84坐标系是美国国防部研制确定的大地坐标系，是一种协议地球坐标系。
WGS-84坐标系的定义是：原点是地球的质心，空间直角坐标系的Z轴指向BIH（1984.0）定义的地极（CTP）方向，即国际协议原点CIO，它由IAU和IUGG共同推荐。
X轴指向BIH定义的零度子午面和CTP赤道的交点，Y轴和Z，X轴构成右手坐标系。
WGS-84椭球采用国际大地测量与地球物理联合会第17届大会测量常数推荐值，采用的两个常用基本几何参数：
长半轴a=6378137m；扁率f=1:298.257223563。
*/
const string WGS84 = "WGS84";

/**
经纬度坐标系, 火星坐标 (GCJ-02)也叫国测局坐标系.
中国标准，从国行移动设备中定位获取的坐标数据使用这个坐标系.
国家规定： 国内出版的各种地图系统（包括电子形式），必须至少采用GCJ-02对地理位置进行首次加密。
*/
const string GCJ02 = "GCJ-02";
/**
经纬度坐标系, 百度坐标 (BD-09).
百度标准，百度 SDK，百度地图，Geocoding 使用.
(本来就乱了，百度又在火星坐标上来个二次加密)。
*/
const string BD09 = "BD-09";
/**
经纬度坐标系, 1954北京坐标系.
1954北京坐标系是将我国大地控制网与前苏联1942年普尔科沃大地坐标系相联结后建立的我国过渡性大地坐标系。
属于参心大地坐标系，采用了前苏联的克拉索夫斯基椭球体。其长半轴 a=6378245，扁率 f=1/298.3。
1954年北京坐标系虽然是苏联1942年坐标系的延伸,但也还不能说它们完全相同
*/
const string BJ54 = "BJ54";
/**
经纬度坐标系, 1980西安坐标系.
*/
const string XA80 = "XA80";
/**
经纬度坐标系, 2000中国标准坐标系.
*/
const string CGS2000 = "CGS2000";

/**
浮点数, 二维数组类, 支持可变长度
*/
class ArrayDouble2D: public JsonBase {
public: 
    /** 说明每个一维数组的元素数量 */
    vector<int32_t> *lenList = NULL;
    /** 一维数组列表 */
    vector<vector<double>*> *dataList = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual ArrayDouble2D* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lenList")) {
            lenList = new vector<int32_t>();
            for (auto& listItem : jsonObj["lenList"].items()){
                lenList->push_back(listItem.value());
            }
        }
        if(jsonObj.contains("dataList")) {
            dataList = new vector<vector<double>*>();
            for (auto& listItem : jsonObj["dataList"].items()){
                vector<double> *templist = new vector<double>();
                for (auto& item3 : listItem.value().items()){
                    templist->push_back(item3.value());
                }
                dataList->push_back(templist);
            }
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json j_vector(*it);
                jsonObj["dataList"].push_back(j_vector);
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("ArrayDouble2D 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json j_vector(*it);
                jsonObj["dataList"].push_back(j_vector);
            }
        }

        return;
    }
public:
    ArrayDouble2D() {
    }
    virtual ~ArrayDouble2D() {
        // 开始释放对象 
        if(lenList) {
            //对象类型指针约定使用new初始化, delete释放
            delete lenList;
        }
        if(dataList) {
            for(auto &it : *dataList) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete dataList;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/**
整数, 二维数组类, 支持可变长度
*/
class ArrayInt2D: public JsonBase {
public: 
    /** 说明每个一维数组的元素数量 */
    vector<int32_t> *lenList = NULL;
    /** 一维数组列表 */
    vector<vector<int32_t>*> *dataList = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual ArrayInt2D* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lenList")) {
            lenList = new vector<int32_t>();
            for (auto& listItem : jsonObj["lenList"].items()){
                lenList->push_back(listItem.value());
            }
        }
        if(jsonObj.contains("dataList")) {
            dataList = new vector<vector<int32_t>*>();
            for (auto& listItem : jsonObj["dataList"].items()){
                vector<int32_t> *templist = new vector<int32_t>();
                for (auto& item3 : listItem.value().items()){
                    templist->push_back(item3.value());
                }
                dataList->push_back(templist);
            }
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json j_vector(*it);
                jsonObj["dataList"].push_back(j_vector);
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("ArrayInt2D 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json j_vector(*it);
                jsonObj["dataList"].push_back(j_vector);
            }
        }

        return;
    }
public:
    ArrayInt2D() {
    }
    virtual ~ArrayInt2D() {
        // 开始释放对象 
        if(lenList) {
            //对象类型指针约定使用new初始化, delete释放
            delete lenList;
        }
        if(dataList) {
            for(auto &it : *dataList) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete dataList;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/**
字符串, 二维数组类, 支持可变长度
*/
class ArrayString2D: public JsonBase {
public: 
    /** 说明每个一维数组的元素数量 */
    vector<int32_t> *lenList = NULL;
    /** 一维数组列表 */
    vector<vector<string>*> *dataList = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual ArrayString2D* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lenList")) {
            lenList = new vector<int32_t>();
            for (auto& listItem : jsonObj["lenList"].items()){
                lenList->push_back(listItem.value());
            }
        }
        if(jsonObj.contains("dataList")) {
            dataList = new vector<vector<string>*>();
            for (auto& listItem : jsonObj["dataList"].items()){
                vector<string> *templist = new vector<string>();
                for (auto& item3 : listItem.value().items()){
                    string value3 = item3.value();
                    templist->push_back(value3);
                }
                dataList->push_back(templist);
            }
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json j_vector(*it);
                jsonObj["dataList"].push_back(j_vector);
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("ArrayString2D 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json j_vector(*it);
                jsonObj["dataList"].push_back(j_vector);
            }
        }

        return;
    }
public:
    ArrayString2D() {
    }
    virtual ~ArrayString2D() {
        // 开始释放对象 
        if(lenList) {
            //对象类型指针约定使用new初始化, delete释放
            delete lenList;
        }
        if(dataList) {
            for(auto &it : *dataList) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete dataList;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/**
浮点数, 三维double数组类, 支持可变长度
*/
class ArrayDouble3D: public JsonBase {
public: 
    /** 说明每个二维数组的元素数量 */
    vector<int32_t> *lenList = NULL;
    /** 二维数组列表 */
    vector<ArrayDouble2D*> *dataList = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual ArrayDouble3D* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lenList")) {
            lenList = new vector<int32_t>();
            for (auto& listItem : jsonObj["lenList"].items()){
                lenList->push_back(listItem.value());
            }
        }
        if(jsonObj.contains("dataList")) {
            dataList = new vector<ArrayDouble2D*>();
            for (auto& listItem : jsonObj["dataList"].items()){
                ArrayDouble2D *vinst = new ArrayDouble2D();
                vinst->parseFromJson(listItem.value());
                dataList->push_back(vinst);
            }
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json subJsonOfIt7879;
                it->toJson(subJsonOfIt7879);
                jsonObj["dataList"].push_back(subJsonOfIt7879);
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("ArrayDouble3D 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json subJsonOfIt423;
                it->toJson(subJsonOfIt423);
                jsonObj["dataList"].push_back(subJsonOfIt423);
            }
        }

        return;
    }
public:
    ArrayDouble3D() {
    }
    virtual ~ArrayDouble3D() {
        // 开始释放对象 
        if(lenList) {
            //对象类型指针约定使用new初始化, delete释放
            delete lenList;
        }
        if(dataList) {
            for(auto &it : *dataList) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete dataList;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/**
整数, 三维double数组类, 支持可变长度
*/
class ArrayInt3D: public JsonBase {
public: 
    /** 说明每个二维数组的元素数量 */
    vector<int32_t> *lenList = NULL;
    /** 二维数组列表 */
    vector<ArrayInt2D*> *dataList = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual ArrayInt3D* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lenList")) {
            lenList = new vector<int32_t>();
            for (auto& listItem : jsonObj["lenList"].items()){
                lenList->push_back(listItem.value());
            }
        }
        if(jsonObj.contains("dataList")) {
            dataList = new vector<ArrayInt2D*>();
            for (auto& listItem : jsonObj["dataList"].items()){
                ArrayInt2D *vinst = new ArrayInt2D();
                vinst->parseFromJson(listItem.value());
                dataList->push_back(vinst);
            }
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json subJsonOfIt1433;
                it->toJson(subJsonOfIt1433);
                jsonObj["dataList"].push_back(subJsonOfIt1433);
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("ArrayInt3D 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json subJsonOfIt840;
                it->toJson(subJsonOfIt840);
                jsonObj["dataList"].push_back(subJsonOfIt840);
            }
        }

        return;
    }
public:
    ArrayInt3D() {
    }
    virtual ~ArrayInt3D() {
        // 开始释放对象 
        if(lenList) {
            //对象类型指针约定使用new初始化, delete释放
            delete lenList;
        }
        if(dataList) {
            for(auto &it : *dataList) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete dataList;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/**
字符串, 三维double数组类, 支持可变长度
*/
class ArrayString3D: public JsonBase {
public: 
    /** 说明每个二维数组的元素数量 */
    vector<int32_t> *lenList = NULL;
    /** 二维数组列表 */
    vector<ArrayString2D*> *dataList = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual ArrayString3D* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lenList")) {
            lenList = new vector<int32_t>();
            for (auto& listItem : jsonObj["lenList"].items()){
                lenList->push_back(listItem.value());
            }
        }
        if(jsonObj.contains("dataList")) {
            dataList = new vector<ArrayString2D*>();
            for (auto& listItem : jsonObj["dataList"].items()){
                ArrayString2D *vinst = new ArrayString2D();
                vinst->parseFromJson(listItem.value());
                dataList->push_back(vinst);
            }
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json subJsonOfIt5385;
                it->toJson(subJsonOfIt5385);
                jsonObj["dataList"].push_back(subJsonOfIt5385);
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("ArrayString3D 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(lenList) {
            for(auto &it : *lenList) {
                jsonObj["lenList"].push_back(it);
            }
        }
        if(dataList) {
            for(auto &it : *dataList) {
                json subJsonOfIt472;
                it->toJson(subJsonOfIt472);
                jsonObj["dataList"].push_back(subJsonOfIt472);
            }
        }

        return;
    }
public:
    ArrayString3D() {
    }
    virtual ~ArrayString3D() {
        // 开始释放对象 
        if(lenList) {
            //对象类型指针约定使用new初始化, delete释放
            delete lenList;
        }
        if(dataList) {
            for(auto &it : *dataList) {
                //对象类型指针约定使用new初始化, delete释放
                delete it;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete dataList;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/**
通用参数
*/
class GeneralParameter: public JsonBase {
public: 
    /** key-value参数列表,一个参数对应一个值 */
    map<string, string> *paraList1 = NULL;
    /** key-list<value>参数列表, 一个参数对应多个值 */
    map<string, vector<string>*> *paraList2 = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual GeneralParameter* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("paraList1")) {
            paraList1 = new map<string,string>();
            for (auto& item : jsonObj["paraList1"].items()){
                string key = item.key();
                string value = item.value();
                paraList1->insert(pair<string,string>(key, value));
            }

        }
        if(jsonObj.contains("paraList2")) {
            paraList2 = new map<string,vector<string>*>();
            for (auto& item : jsonObj["paraList2"].items()){
                string key = item.key();
                vector<string> *templist = new vector<string>();
                for (auto& item3 : item.value().items()){
                    string value3 = item3.value();
                    templist->push_back(value3);
                }
                paraList2->insert(pair<string,vector<string>*>(key, templist));
            }

        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(paraList1) {
            for(auto &it : *paraList1) {
                string key = it.first;
                string value = it.second;
                jsonObj["paraList1"][key] = value;
            }
        }
        if(paraList2) {
            for(auto &it : *paraList2) {
                string key = it.first;
                vector<string>* value = it.second;
                json j_vector(*value);
                jsonObj["paraList2"][key] = j_vector;
            }
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("GeneralParameter 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(paraList1) {
            for(auto &it : *paraList1) {
                string key = it.first;
                string value = it.second;
                jsonObj["paraList1"][key] = value;
            }
        }
        if(paraList2) {
            for(auto &it : *paraList2) {
                string key = it.first;
                vector<string>* value = it.second;
                json j_vector(*value);
                jsonObj["paraList2"][key] = j_vector;
            }
        }

        return;
    }
public:
    GeneralParameter() {
    }
    virtual ~GeneralParameter() {
        // 开始释放对象 
        if(paraList1) {
            //对象类型指针约定使用new初始化, delete释放
            delete paraList1;
        }
        if(paraList2) {
            for(auto &it : *paraList2) {
                vector<string>* value = it.second;
                //对象类型指针约定使用new初始化, delete释放
                delete value;
            }
            //对象类型指针约定使用new初始化, delete释放
            delete paraList2;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/** 经度,纬度对象 */
class LngLat: public JsonBase {
public: 
    /** 经度, WGS84坐标系, 精确到小数点后7位 */
    double lng;
    /** 纬度, WGS84坐标系, 精确到小数点后7位 */
    double lat;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual LngLat* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lng")) {
            lng = jsonObj["lng"];
        }
        if(jsonObj.contains("lat")) {
            lat = jsonObj["lat"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("LngLat 内存不足, toJsonString失败!\n");
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

        return;
    }
public:
    LngLat() {
        lng = 0;
        lat = 0;
    }
    virtual ~LngLat() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};
class LngLatInt: public JsonBase {
public: 
    /** 经度, WGS84坐标系, 精确到小数点后7位, 乘以10000000 */
    int32_t lng;
    /** 纬度, WGS84坐标系, 精确到小数点后7位, 乘以10000000 */
    int32_t lat;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual LngLatInt* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lng")) {
            lng = jsonObj["lng"];
        }
        if(jsonObj.contains("lat")) {
            lat = jsonObj["lat"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("LngLatInt 内存不足, toJsonString失败!\n");
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

        return;
    }
public:
    LngLatInt() {
        lng = 0;
        lat = 0;
    }
    virtual ~LngLatInt() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};
/** 经度,纬度,高度对象 */
class LngLatHgt: public JsonBase {
public: 
    /** 经度, WGS84坐标系, 精确到小数点后7位 */
    double lng;
    /** 纬度, WGS84坐标系, 精确到小数点后7位 */
    double lat;
    /** 离地高度, 单位:米, 精确到小数点后1位 */
    float ht;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual LngLatHgt* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lng")) {
            lng = jsonObj["lng"];
        }
        if(jsonObj.contains("lat")) {
            lat = jsonObj["lat"];
        }
        if(jsonObj.contains("ht")) {
            ht = jsonObj["ht"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("LngLatHgt 内存不足, toJsonString失败!\n");
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

        return;
    }
public:
    LngLatHgt() {
        lng = 0;
        lat = 0;
        ht = 0;
    }
    virtual ~LngLatHgt() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};
class LngLatHgtInt: public JsonBase {
public: 
    /** 经度, WGS84坐标系, 精确到小数点后7位, 乘以10000000 */
    int32_t lng;
    /** 纬度, WGS84坐标系, 精确到小数点后7位, 乘以10000000 */
    int32_t lat;
    /** 离地高度, 单位:米, 精确到小数点后1位, 乘以100 */
    int32_t ht;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual LngLatHgtInt* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("lng")) {
            lng = jsonObj["lng"];
        }
        if(jsonObj.contains("lat")) {
            lat = jsonObj["lat"];
        }
        if(jsonObj.contains("ht")) {
            ht = jsonObj["ht"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("LngLatHgtInt 内存不足, toJsonString失败!\n");
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

        return;
    }
public:
    LngLatHgtInt() {
        lng = 0;
        lat = 0;
        ht = 0;
    }
    virtual ~LngLatHgtInt() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};
/** 经度,纬度,高度,海拔对象 */
class LngLatHgtAlt: public JsonBase {
public: 
    /** 经度, WGS84坐标系, 精确到小数点后7位 */
    double lng;
    /** 纬度, WGS84坐标系, 精确到小数点后7位 */
    double lat;
    /** 离地高度, 单位:米, 精确到小数点后1位 */
    float ht;
    /** 海拔高度, 单位:米, 精确到小数点后1位 */
    float alt;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual LngLatHgtAlt* parseFromJson(const json& jsonObj) {
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
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("LngLatHgtAlt 内存不足, toJsonString失败!\n");
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

        return;
    }
public:
    LngLatHgtAlt() {
        lng = 0;
        lat = 0;
        ht = 0;
        alt = 0;
    }
    virtual ~LngLatHgtAlt() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};
class LngLatHgtAltInt: public JsonBase {
public: 
    /** 经度, WGS84坐标系, 精确到小数点后7位, 乘以10000000 */
    int32_t lng;
    /** 纬度, WGS84坐标系, 精确到小数点后7位, 乘以10000000 */
    int32_t lat;
    /** 离地高度, 单位:米, 精确到小数点后1位, 乘以100 */
    int32_t ht;
    /** 海拔高度, 单位:米, 精确到小数点后1位, 乘以100 */
    int32_t alt;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual LngLatHgtAltInt* parseFromJson(const json& jsonObj) {
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
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("LngLatHgtAltInt 内存不足, toJsonString失败!\n");
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

        return;
    }
public:
    LngLatHgtAltInt() {
        lng = 0;
        lat = 0;
        ht = 0;
        alt = 0;
    }
    virtual ~LngLatHgtAltInt() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/**
位置对象, 同LngLatHgtAlt
*/
class Location : public JsonBase {
public: 
    /** 经度, WGS84坐标系, 精确到小数点后7位 */
    double lng;
    /** 纬度, WGS84坐标系, 精确到小数点后7位 */
    double lat;
    /** 离地高度, 单位:米, 精确到小数点后1位 */
    float ht;
    /** 海拔高度, 单位:米, 精确到小数点后1位 */
    float alt;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual Location* parseFromJson(const json& jsonObj) {
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
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["lng"] = lng;
        jsonObj["lat"] = lat;
        jsonObj["ht"] = ht;
        jsonObj["alt"] = alt;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("Location 内存不足, toJsonString失败!\n");
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

        return;
    }
public:
    Location() {
        lng = 0;
        lat = 0;
        ht = 0;
        alt = 0;
    }
    virtual ~Location() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/**
飞行时间段, 时间戳, 精确到秒
*/
class TimeSlice: public JsonBase {
public: 
    /** 起始时间, 北京时间戳, 精确到秒, 围栏有效时间 */
    int32_t begin;
    /** 结尾时间, 北京时间戳, 精确到秒, 围栏有效时间 */
    int32_t end;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual TimeSlice* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("begin")) {
            begin = jsonObj["begin"];
        }
        if(jsonObj.contains("end")) {
            end = jsonObj["end"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["begin"] = begin;
        jsonObj["end"] = end;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("TimeSlice 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["begin"] = begin;
        jsonObj["end"] = end;

        return;
    }
public:
    TimeSlice() {
        begin = 0;
        end = 0;
    }
    virtual ~TimeSlice() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};
/**
飞行时间段, 时间戳, 精确到毫秒
*/
class TimeStampSlice: public JsonBase {
public: 
    /** 起始时间, 北京时间戳, 精确到毫秒, 围栏有效时间 */
    int64_t begin;
    /** 结尾时间, 北京时间戳, 精确到毫秒, 围栏有效时间 */
    int64_t end;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual TimeStampSlice* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("begin")) {
            begin = jsonObj["begin"];
        }
        if(jsonObj.contains("end")) {
            end = jsonObj["end"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["begin"] = begin;
        jsonObj["end"] = end;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("TimeStampSlice 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["begin"] = begin;
        jsonObj["end"] = end;

        return;
    }
public:
    TimeStampSlice() {
        begin = 0;
        end = 0;
    }
    virtual ~TimeStampSlice() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/**
通用传感器参数定义
*/
class Sensor: public JsonBase {
public: 
    /** 参数名 */
    string k;
    /** 参数值 */
    string v;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual Sensor* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("k")) {
            k = jsonObj["k"];
        }
        if(jsonObj.contains("v")) {
            v = jsonObj["v"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(!k.empty()) {
            jsonObj["k"] = k;
        }
        if(!v.empty()) {
            jsonObj["v"] = v;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("Sensor 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(!k.empty()) {
            jsonObj["k"] = k;
        }
        if(!v.empty()) {
            jsonObj["v"] = v;
        }

        return;
    }
public:
    Sensor() {
    }
    virtual ~Sensor() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/**
机场, 用于起飞点或降落点. 待完善
注意: loc字段设为2dsphere索引.
*/
class Airport: public JsonBase {
public: 
    /** id编号, 由数据库自动生成 */
    string id;
    /** 名称 */
    string name;
    /** 类型（0-起飞点，1-投递点, 2-起飞点或降落点, 3-机库） */
    int32_t type = 0;
    /** 中心位置 */
    Location *pos = NULL;
    /** XYZ方向的缩放 …… 待确定*/
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual Airport* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("id")) {
            id = jsonObj["id"];
        }
        if(jsonObj.contains("name")) {
            name = jsonObj["name"];
        }
        if(jsonObj.contains("type")) {
            type = jsonObj["type"];
        }
        if(jsonObj.contains("pos")) {
            pos = new Location();
            pos->parseFromJson(jsonObj["pos"]);
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(!id.empty()) {
            jsonObj["id"] = id;
        }
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        jsonObj["type"] = type;
        if(pos) {
            json subJsonOfPos;
            pos->toJson(subJsonOfPos);
            jsonObj["pos"] = subJsonOfPos;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("Airport 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(!id.empty()) {
            jsonObj["id"] = id;
        }
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        jsonObj["type"] = type;
        if(pos) {
            json subJsonOfPos;
            pos->toJson(subJsonOfPos);
            jsonObj["pos"] = subJsonOfPos;
        }

        return;
    }
public:
    Airport() {
    }
    virtual ~Airport() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(pos) {
            delete pos;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

/**
影像/高程文件信息. 待完善
注意: locs字段设为2dsphere索引.
*/
class ImageTerrain: public JsonBase {
public: 
    string id;
    /** 名称 */
    string name;
    /** 文件访问链接 */
    string url;
    /** 文件类型, 0:高程, 1:影像 */
    int32_t type;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual ImageTerrain* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("id")) {
            id = jsonObj["id"];
        }
        if(jsonObj.contains("name")) {
            name = jsonObj["name"];
        }
        if(jsonObj.contains("url")) {
            url = jsonObj["url"];
        }
        if(jsonObj.contains("type")) {
            type = jsonObj["type"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(!id.empty()) {
            jsonObj["id"] = id;
        }
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        if(!url.empty()) {
            jsonObj["url"] = url;
        }
        jsonObj["type"] = type;

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("ImageTerrain 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(!id.empty()) {
            jsonObj["id"] = id;
        }
        if(!name.empty()) {
            jsonObj["name"] = name;
        }
        if(!url.empty()) {
            jsonObj["url"] = url;
        }
        jsonObj["type"] = type;

        return;
    }
public:
    ImageTerrain() {
        type = 0;
    }
    virtual ~ImageTerrain() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/**
风力信息. 待完善
*/
class Wind: public JsonBase {
public: 
    /** 风向 */
    int32_t head;
    /** 风速 */
    int32_t spd;
    /** 风力情况, 如阵风 */
    int32_t gust;
    /** 风力描述, 如5级 */
    string wind;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual Wind* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("head")) {
            head = jsonObj["head"];
        }
        if(jsonObj.contains("spd")) {
            spd = jsonObj["spd"];
        }
        if(jsonObj.contains("gust")) {
            gust = jsonObj["gust"];
        }
        if(jsonObj.contains("wind")) {
            wind = jsonObj["wind"];
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        jsonObj["head"] = head;
        jsonObj["spd"] = spd;
        jsonObj["gust"] = gust;
        if(!wind.empty()) {
            jsonObj["wind"] = wind;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("Wind 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        jsonObj["head"] = head;
        jsonObj["spd"] = spd;
        jsonObj["gust"] = gust;
        if(!wind.empty()) {
            jsonObj["wind"] = wind;
        }

        return;
    }
public:
    Wind() {
        head = 0;
        spd = 0;
        gust = 0;
    }
    virtual ~Wind() {
        // 开始释放对象 
        //TODO, 在这里添加额外的释放处理
    }
};

/**
天气. 待完善
*/
class Weather : public JsonBase {
public: 
    string id;
    /** 地名 */
    string city;
    /** 雨量信息 */
    string rain;
    /** 雪量信息 */
    string snow;
    /** 风力信息 */
    Wind *wind = NULL;
    /** 时间段 */
    TimeSlice *time = NULL;
public: 
    /** 注意: 返回结果需要delete释放! */
    virtual Weather* parseFromJson(const json& jsonObj) {
        if(jsonObj.contains("id")) {
            id = jsonObj["id"];
        }
        if(jsonObj.contains("city")) {
            city = jsonObj["city"];
        }
        if(jsonObj.contains("rain")) {
            rain = jsonObj["rain"];
        }
        if(jsonObj.contains("snow")) {
            snow = jsonObj["snow"];
        }
        if(jsonObj.contains("wind")) {
            wind = new Wind();
            wind->parseFromJson(jsonObj["wind"]);
        }
        if(jsonObj.contains("time")) {
            time = new TimeSlice();
            time->parseFromJson(jsonObj["time"]);
        }
        return this;
    }
    /** 注意: 返回结果需要free释放! */
    virtual char* toJsonString() {
        json jsonObj;
        if(!id.empty()) {
            jsonObj["id"] = id;
        }
        if(!city.empty()) {
            jsonObj["city"] = city;
        }
        if(!rain.empty()) {
            jsonObj["rain"] = rain;
        }
        if(!snow.empty()) {
            jsonObj["snow"] = snow;
        }
        if(wind) {
            json subJsonOfWind;
            wind->toJson(subJsonOfWind);
            jsonObj["wind"] = subJsonOfWind;
        }
        if(time) {
            json subJsonOfTime;
            time->toJson(subJsonOfTime);
            jsonObj["time"] = subJsonOfTime;
        }

        string jsonStr = jsonObj.dump();
        int jsonLen = jsonStr.length();
        char *res = (char*)malloc(jsonLen+8);
        if(!res) {
            printf("Weather 内存不足, toJsonString失败!\n");
            return NULL;
        }
        memcpy(res, jsonStr.c_str(), jsonLen);
        res[jsonLen] = 0;
        return res;
    }
    /** 构建json对象 */
    virtual void toJson(json &jsonObj) {
        if(!id.empty()) {
            jsonObj["id"] = id;
        }
        if(!city.empty()) {
            jsonObj["city"] = city;
        }
        if(!rain.empty()) {
            jsonObj["rain"] = rain;
        }
        if(!snow.empty()) {
            jsonObj["snow"] = snow;
        }
        if(wind) {
            json subJsonOfWind;
            wind->toJson(subJsonOfWind);
            jsonObj["wind"] = subJsonOfWind;
        }
        if(time) {
            json subJsonOfTime;
            time->toJson(subJsonOfTime);
            jsonObj["time"] = subJsonOfTime;
        }

        return;
    }
public:
    Weather() {
    }
    virtual ~Weather() {
        // 开始释放对象 
        //对象类型指针约定使用new初始化, delete释放
        if(wind) {
            delete wind;
        }
        //对象类型指针约定使用new初始化, delete释放
        if(time) {
            delete time;
        }
        //TODO, 在这里添加额外的释放处理
    }
};

} 
