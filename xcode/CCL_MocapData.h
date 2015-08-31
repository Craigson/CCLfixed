/*
 #pragma once

#include "cinder/Json.h"
#include "CCL_MocapJoint.h"
#include "cinder/Vector.h"
#include "Jzon.h"

class CCL_MocapData
{
public:
    CCL_MocapData(int skip, std::vector<CCL_MocapJoint>& mJoints);
    CCL_MocapData(std::string filename, std::vector<CCL_MocapJoint>& mJoints);
std::vector<CCL_MocapJoint> loadMotionCaptureFromJson(const ci::fs::path &file);
std::vector<CCL_MocapJoint> loadMotionCaptureFromSite(const ci::Url &url, int skip);

void addUUIDtoJoint(const std::string &grp, const std::string &title, const std::string &uuid, int skip, std::vector<CCL_MocapJoint>& output_joints);

const std::string URL_STREAM_JSON = "http://api.piecemeta.com/channels/c51be7cc-a985-4c4a-a53b-fa034d33fff8/streams.json";
const std::string URL_STREAM_REQ = "http://api.piecemeta.com/streams/";

}; // namespace ccl

*/
 
#pragma once

#include "cinder/Json.h"
#include "CCL_MocapJoint.h"
#include "cinder/Vector.h"
#include "Jzon.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CCL_MocapData {
public:
    //   CCL_MocapData(int skip);
    //   CCL_MocapData(const string &url, int skip);
    CCL_MocapData(int skip, std::vector<CCL_MocapJoint>& mJoints);
    CCL_MocapData(string filename, vector<CCL_MocapJoint>& mJoints);
    
    void loadChannel(const string &url, int skip);
    void addUUIDtoJoint( string grp,  string title,  string uuid, int skip, std::vector<CCL_MocapJoint>& mJoints);
    
    //    vector<CCL_MocapJoint> mJoints;
    string fileName;
    
private:
    // default URL
    static constexpr const char* URL_STREAM_JSON = "http://api.piecemeta.com/channels/d543a0f3-6da2-4346-9a98-33ed40370ffd/streams.json";
    static constexpr const char * URL_STREAM_REQ = "http://api.piecemeta.com/streams/";
};