#include "CCL_MocapData.h"
#include "cinder/gl/gl.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class CCL_Dancer {
public:
    CCL_Dancer( string jsonFileName, int skip, int framerate);
    vector<vec3> getJointPositionsAtFrame(int frame);
    void updateJointPositionAtFrame(int frame);
    
    string fileName;
    int skip;
    int frameRate;
    int totalFrame;
    int jointSize;
    
    // GL STUFF
    gl::BatchRef        mSphereBatch;
    gl::VboRef			mInstanceDataVbo;
    gl::GlslProgRef		mGlsl;
    gl::GlslProgRef     solidShader;
    
private:
    vector<CCL_MocapJoint> jointList;
};