#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CameraUi.h"
#include "cinder/Json.h"
#include "cinder/Utilities.h"
#include "cinder/Log.h"
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include "CCL_MocapData.h"
#include "Skeleton.h"
#include "RibbonFunctions.h"
#include "cinder/Easing.h"
#include "Trail.h"
#include "CCL_Dancer.h"

/************* UI *************/
#include "CinderImGui.h"
/************* UI *************/


using namespace ci;
using namespace ci::app;
using namespace std;

struct Ribbon
{
    vec3              _target;
    std::vector<vec3> _spine;
    std::vector<vec3> _triangles;
    size_t            _joint_index = 0;
};



/*----------------------- NOTES FOR IMPROVEMENTS ---------------------------
 
 CHANGE ALL vectors TO lists TO IMPROVE EFFICIENCY (AS NO RANDOM INDEX ACCESS IS
 REQUIRED - USE ITERS.
 
 ADD TOP, FRONT, SIDE VIEWS TO GUI
 
 
 
 --------------------------------------------------------------------------*/

//GLOBAL VARIABLES
//const float DRAW_SCALE = 200;       //SCALE FOR DRAWING THE POINTS
int FRAME_COUNT;
int TOTAL_FRAMES;

/************* UI *************/
BOOL paused;
BOOL drawRibbons;
BOOL drawPhysics;
BOOL drawSkeleton;

int CURRENT_DATA_SET = 0;
int LOADED_DATA_SET = 0;

//VARIABLES FOR MULTIPLE DANCERS
bool isDancer1 = true;
int fpsDancer1 = 24;

bool isDancer2 = false;
int fpsDancer2 = 60;

bool isDancer3 = false;
int fpsDancer3 = 60;

bool isDancer4 = false;
int fpsDancer4 = 60;

bool isDancer5 = false;
int fpsDancer5 = 30;

bool isDancer6 = false;
int fpsDancer6 = 30;

int CinderFrameReate = 60;
/************* UI *************/


class CCLfixedApp : public App {
public:
    // static void prepareSettings( Settings *settings );
    
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void mouseDrag (MouseEvent event) override;
    void update() override;
    void draw() override;
    
    void keyDown(KeyEvent event) override;
    
    void setupEnviron( int xSize, int zSize, int spacing );     //METHOD FOR SETTING UP THE 3D ENVIRONMENT
    void renderScene();                                         //METHOD FOR RENDERING THE 3D ENVIRONMENT
    void initData();                                            //METHOD FOR IMPORTING JSON DATA
    void setupShader();
    
    void drawRibbons();
    void updateRibbons();
    void updateSequence();
    
    std::vector<vec3> distortLimbs(const std::vector<vec3>& normalLimbs, float scaleFactor);
    
    //CREATE A VERTEX BATCH FOR THE FLOOR MESH
    gl::VertBatchRef	mGridMesh;
    
    CameraPersp			mCamera;
    CameraUi			mCamUi;
    
    std::vector<CCL_MocapJoint> jointList;  //GLOBAL CONTAINER TO HOLD THE JOINT POSITIONS
    
    //TEST SPHERES
    gl::BatchRef        mSphereBatch;
    gl::VboRef			mInstanceDataVbo;
    
    gl::GlslProgRef		mGlsl;
    gl::GlslProgRef     solidShader;
    
    
    //CREATE A CONTAINER TO STORE THE POSITION OF EACH JOINT FOR A SINGLE FRAME
    std::vector<glm::vec3> framePositions;
    std::vector<glm::vec3> distortedJoints;
    std::vector<Ribbon> ribbons;
    
    typedef vector<glm::vec3>::size_type bodySize;
    // bodySize sizeOfBody = jointPositions.size();
    
   // Skeleton skeleton;
    
   // Trail handTrail;
    
    bool limbsDistorted = false;
    bool ribbonsActive = false;
    bool trailsActive = true;
    
   // CCL_MocapData * mocapData;
    
    
    void loadDancers();
    std::vector<CCL_Dancer> dancers;
};


//--------------------- SETUP ----------------------------------

void CCLfixedApp::setup()
{
    
    setFrameRate(12);
    
    //SETUP THE 3D ENVIRONMENT
    setupEnviron( 5000, 5000, 100 );
    
    //SETUP THE CAMERA
    mCamera.lookAt( vec3( 500, 500, 0 ), vec3( 0 ) );
    
    mCamera.setEyePoint(vec3(500,1000,0));
    
    mCamera.setFarClip(20000);
    
    /************* UI *************/
    
    // THIS HAS BE DONE BEFORE "CameraUI" //
    ui::initialize();
    
    /************* UI *************/
    
    //mCamera.setEyePoint(vec3(0,200,650));
    mCamUi = CameraUi( &mCamera, getWindow() );
    
    //setupShader();
    
    //initData(); //IMPORT THE JSON DATA AND SORT IT INTO A LIST
    
    limbsDistorted = false;
    
    /* THIS JUST PRINTS OUT THE POSITIONS OF THE FIRST JOINT TO CHECK THAT IT'S LOADED CORRECTLY
     for (int i = 0; i < 1; i++){
     for (int j = 0; j < jointList[i].jointPositions.size(); j++){
     std::cout << j << ": " << jointList[i].jointPositions[j] << std::endl;
     }
     }
     */
    
    
    FRAME_COUNT = 0;
    //TOTAL_FRAMES = jointList[0].jointPositions.size(); //SHOULD PROBABLY PUT A TRY/CATCH HERE
    TOTAL_FRAMES = 6400;
    
    std::cout << "total frames: " << TOTAL_FRAMES << std::endl;
    
//    gl::VboMeshRef body = gl::VboMesh::create( geom::Sphere().subdivisions( 16 ).radius(2) );
    
    
//    // CREATE THE SPHERES AT THE INITIAL JOINT LOCATIONS
//    for ( int i = 0; i < jointList.size(); ++i ) {
//        float instanceX = jointList[i].jointPositions[0].x;
//        float instanceY = jointList[i].jointPositions[0].y;
//        float instanceZ = jointList[i].jointPositions[0].z;
//        // float instanceZ = 0;
//        
//        framePositions.push_back( vec3( instanceX, instanceY, instanceZ));
//    }
//    
//    skeleton = Skeleton(framePositions);

    
 //----------------   handTrail = Trail(framePositions[17]);
    
    
    //std::cout << "positions: " << positions[0] << std::endl;
    
    
    
//    // create the VBO which will contain per-instance (rather than per-vertex) data
//    mInstanceDataVbo = gl::Vbo::create( GL_ARRAY_BUFFER, framePositions.size() * sizeof(vec3), framePositions.data(), GL_DYNAMIC_DRAW );
//    
//    // we need a geom::BufferLayout to describe this data as mapping to the CUSTOM_0 semantic, and the 1 (rather than 0) as the last param indicates per-instance (rather than per-vertex)
//    geom::BufferLayout instanceDataLayout;
//    
//    instanceDataLayout.append( geom::Attrib::CUSTOM_0, 3, 0, 0, 1 /* per instance */ );
//    
//    //NOW ADD IT TO THE VBO MESH THAT WE INITIAL CREATED FOR THE BODY / SKELETON
//    body->appendVbo( instanceDataLayout, mInstanceDataVbo );
//    
//    //FINALLY, BUILD THE BATCH, AND MAP THE CUSTOM_0 ATTRIBUTE TO THE "vInstancePosition" GLSL VERTEX ATTRIBUTE
//    mSphereBatch = gl::Batch::create( body, mGlsl, { { geom::Attrib::CUSTOM_0, "vInstancePosition" } } );
//    
    gl::enableDepthWrite();
    gl::enableDepthRead();
    
    //PRINT OUT JOINT INDEX AND NAME OF JOINT
    
//    for (int i = 0; i < jointList.size(); i++)
//    {
//        std::cout << "index: " << i << ", Joint name: " << jointList[i].jointName << std::endl;
//    }
  
    /*
    //SETUP RIBBONS
    for (auto i = 0; i < jointList.size(); i += 1)
    {
        auto r = Ribbon();
        auto pos = framePositions[i];
        r._spine.assign(10, pos);
        r._joint_index = i;
        r._target = pos;
        ribbons.push_back(r);
    }
    
    //SETUP TRAILS
    */
    
    loadDancers();
    
}

//--------------------- MOUSEDOWN ------------------------------

void CCLfixedApp::mouseDown( MouseEvent event )
{
}


//----------------------- UPDATE -------------------------------

void CCLfixedApp::update()
{
    
    /************* UI *************/
    if(paused)
        return;
    /************* UI *************/
    
    //UPDATE VARIABLES FOR ALL DANCERS
    if( isDancer1 ){
        dancers[0].updateJointPositionAtFrame(FRAME_COUNT/(CinderFrameReate/fpsDancer1));
    }
    
    if( isDancer2 ){
        dancers[1].updateJointPositionAtFrame(FRAME_COUNT/(CinderFrameReate/fpsDancer1));
    }
    
    if( isDancer3 ){
        dancers[2].updateJointPositionAtFrame(FRAME_COUNT/(CinderFrameReate/fpsDancer1));
    }
    
    if( isDancer4 ){
        dancers[3].updateJointPositionAtFrame(FRAME_COUNT/(CinderFrameReate/fpsDancer1));
    }
    
    if( isDancer5 ){
        dancers[4].updateJointPositionAtFrame(FRAME_COUNT/(CinderFrameReate/fpsDancer1));
    }
    
    if( isDancer6 ){
        dancers[5].updateJointPositionAtFrame(FRAME_COUNT/(CinderFrameReate/fpsDancer1));
    }
    
    //  std::cout << mCamera.getEyePoint() << std::endl;
    
    //UPDATE POSITIONS
    //MAP INSTANCE DATA TO VBO
    //WRITE NEW POSITIONS
    //UNMAP
    
    /*
    glm::vec3 *newPositions = (glm::vec3*)mInstanceDataVbo->mapReplace();
    
    for( int i = 0; i < jointList.size(); ++i ) {
        
        float instanceX = jointList[i].jointPositions[FRAME_COUNT].x;
        float instanceY = jointList[i].jointPositions[FRAME_COUNT].y;
        float instanceZ = jointList[i].jointPositions[FRAME_COUNT].z;
        
        vec3 newPos(vec3(instanceX,instanceY, instanceZ)); //CREATE A NEW VEC3 FOR UPDATING THE VBO
        
        framePositions[i] = newPos;
        
        //distortedJoints.push_back(newPos);
        
    }
    
    //REPLACE VEC3s IN VBO BY INCREMENTING THE POINTER
    for (int i = 0; i < framePositions.size(); i++){
        *newPositions++ = framePositions[i];
    }
    
     */
    
  //  handTrail.update(framePositions[17]);
    
//    std::cout << framePositions[17] << std::endl;
    

     //   skeleton.update(framePositions);
    /*
    if (limbsDistorted){
        skeleton.update(distortLimbs(framePositions,5));
    } else {
        skeleton.update(framePositions);
    }
    */
    //mInstanceDataVbo->unmap();
    // std::cout << "position: " << positions[0] << std::endl;
    
  //  if (ribbonsActive)updateRibbons();
    
    //MANUALLY INCREMENT THE FRAME, IF THE FRAME_COUNT EXCEEDS TOTAL FRAMES, RESET THE COUNTER
    if (FRAME_COUNT < TOTAL_FRAMES)
    {
        FRAME_COUNT += 1;
    } else {
        FRAME_COUNT = 0;
    }
    
    std::cout << getAverageFps() << std:: endl;
    // std::cout << "frame rate: " << getAverageFps() << ", frame count: " << FRAME_COUNT << std::endl;
    
    //define changed color
    //mGlsl->uniform("uColor", changedColor);
}

//--------------------------- DRAW -----------------------------

void CCLfixedApp::draw()
{
    
    gl::clear(Color(0.1f,0.1f,0.1f) );
    
    /************* UI *************/
    
    static int frameRage = 12;
    ui::InputInt("FPS", &frameRage);
    setFrameRate(frameRage);
    
    if( ui::Button("PLAY") ){
        paused = false;
    }
    if( ui::Button("PAUSE") ){
        paused = true;
    }
    
    if (ui::Checkbox("DRAW RIBBONS", &ribbonsActive)){
        ribbonsActive = true;
    }
    
    
    ui::SliderInt("PROGRESS", &FRAME_COUNT, 0, TOTAL_FRAMES);
    
    vector<std::string> dataVector = {"CCL_JOINT_CCL3_00_skip10.json",
        "CCL_JOINT_CCL4_00_skip4.json",
        "CCL_JOINT_CCL4_01_skip4.json",
        "CCL_JOINT_CCL4_02_skip4.json",
        "CCL_JOINT_CCL4_03_skip8.json",
        "CCL_JOINT_CCL4_04_skip8.json"};
    
    ui::Checkbox("Dancer1", &isDancer1);
    ui::InputInt("D1 FPS", &fpsDancer1);
    
    ui::Checkbox("Dancer2", &isDancer2);
    ui::InputInt("D2 FPS", &fpsDancer2);
    
    ui::Checkbox("Dancer3", &isDancer3);
    ui::InputInt("D3 FPS", &fpsDancer3);
    
    ui::Checkbox("Dancer4", &isDancer4);
    ui::InputInt("D4 FPS", &fpsDancer4);
    
    ui::Checkbox("Dancer5", &isDancer5);
    ui::InputInt("D5 FPS", &fpsDancer5);
    
    ui::Checkbox("Dancer6", &isDancer6);
    ui::InputInt("D6 FPS", &fpsDancer6);
    /********** DATA ____ GUI ***********************/
   
    /*
    vector<std::string> dataVector = {"CCL_JOINT_CCL3_00_skip10.json",
        "CCL_JOINT_CCL4_00_skip4.json",
        "CCL_JOINT_CCL4_01_skip4.json",
        "CCL_JOINT_CCL4_02_skip4.json",
        "CCL_JOINT_CCL4_03_skip8.json",
        "CCL_JOINT_CCL4_04_skip8.json"};
    
    ui::ListBox("DATA", &CURRENT_DATA_SET, dataVector);
    
    if( CURRENT_DATA_SET != LOADED_DATA_SET){
        //     paused = true;
        
        
     //   jointList = {};
        jointList = ccl::loadMotionCaptureFromJson(getAssetPath(dataVector[CURRENT_DATA_SET]));

        FRAME_COUNT = 0;
        TOTAL_FRAMES = jointList[0].jointPositions.size(); //SHOULD PROBABLY PUT A TRY/CATCH HERE
        
        std::cout << "total frames: " << TOTAL_FRAMES << ", total joints:"<< jointList.size() << std::endl;
        
        gl::VboMeshRef body = gl::VboMesh::create( geom::Sphere().subdivisions( 16 ).radius(4) );
        
        //CREATE A CONTAINER TO STORE THE INITIAL POSITIONS FOR INITIALISING THE JOINTS
        std::vector<glm::vec3> positions;
        
        // CREATE THE SPHERES AT THE INITIAL JOINT LOCATIONS
        for ( int i = 0; i < jointList.size(); ++i ) {
            glm::vec3 jointAt = jointList[i].jointPositions[i];
            float instanceX = jointAt.x;
            float instanceY = jointAt.y;
            float instanceZ = jointAt.z;
            // float instanceZ = 0;
            
            positions.push_back( vec3( instanceX, instanceY, instanceZ));
        }
        //std::cout << "positions: " << positions[0] << std::endl;
        
        // create the VBO which will contain per-instance (rather than per-vertex) data
        mInstanceDataVbo = gl::Vbo::create( GL_ARRAY_BUFFER, positions.size() * sizeof(vec3), positions.data(), GL_DYNAMIC_DRAW );
        
        // we need a geom::BufferLayout to describe this data as mapping to the CUSTOM_0 semantic, and the 1 (rather than 0) as the last param indicates per-instance (rather than per-vertex)
        geom::BufferLayout instanceDataLayout;
        
        instanceDataLayout.append( geom::Attrib::CUSTOM_0, 3, 0, 0, 1 per instance  );
        
        //NOW ADD IT TO THE VBO MESH THAT WE INITIAL CREATED FOR THE BODY / SKELETON
        body->appendVbo( instanceDataLayout, mInstanceDataVbo );
        
        //FINALLY, BUILD THE BATCH, AND MAP THE CUSTOM_0 ATTRIBUTE TO THE "vInstancePosition" GLSL VERTEX ATTRIBUTE
        mSphereBatch = gl::Batch::create( body, mGlsl, { { geom::Attrib::CUSTOM_0, "vInstancePosition" } } );
        
        LOADED_DATA_SET = CURRENT_DATA_SET;
        
    }
*/
    /********** DATA ____ GUI ***********************/
    
    gl::setMatrices( mCamera );
    
    
    
    renderScene();
    
    gl::color( 1, 0, 0 );
    //gl::ScopedModelMatrix modelScope;
    //mSphereBatch->drawInstanced( sizeOfBody );
    
    //mSphereBatch->drawInstanced( jointList.size() );
    //skeleton.renderPhysics(true);
    
    //skeleton.renderStatic();
    
    
    if( isDancer1){
        dancers[0].mSphereBatch->drawInstanced(dancers[0].jointSize);
        
    }
    if( isDancer2){
        dancers[1].mSphereBatch->drawInstanced(dancers[1].jointSize);
        
    }
    if( isDancer3){
        dancers[2].mSphereBatch->drawInstanced(dancers[2].jointSize);
        
    }
    if ( isDancer4){
        dancers[3].mSphereBatch->drawInstanced(dancers[3].jointSize);
        
    }
    if( isDancer5){
        dancers[4].mSphereBatch->drawInstanced(dancers[4].jointSize);
        
    }
    if( isDancer6){
        dancers[5].mSphereBatch->drawInstanced(dancers[5].jointSize);
    }
    
    
  //  if (ribbonsActive)drawRibbons();
    
 //   if(trailsActive)handTrail.render();

}

//------------------- MOUSE DRAGGED ------------------------------

void CCLfixedApp::mouseDrag( MouseEvent event )
{
    mCamUi.mouseDrag( event );
}

//--------------------  KEY DOWN -----------------------------

void CCLfixedApp::keyDown (KeyEvent event) {
//skeleton.pushone(vec3(200,200,0));
}

//------------------- SETUP THE ENVIRONMENT / GRID -----------------------

void CCLfixedApp::setupEnviron( int xSize, int zSize, int spacing )
{
    CI_ASSERT( ( spacing <= xSize ) && ( spacing <= zSize ) );
    
    // Cut in half and adjust for spacing.
    xSize = ( ( xSize / 2 ) / spacing ) * spacing;
    zSize = ( ( zSize / 2 ) / spacing ) * spacing;
    
    const int xMax = xSize + spacing;
    const int zMax = zSize + spacing;
    const ColorA defaultColor( 0.9f, 0.9f, 0.9f,0.1f);
    const ColorA black( 0, 0, 0, 1 );
    
    mGridMesh = gl::VertBatch::create( GL_LINES );
    
    // Add x lines.
    for( int xVal = -xSize; xVal < xMax; xVal += spacing ) {
        mGridMesh->color( defaultColor );
        mGridMesh->vertex( (float)xVal, 0, (float)-zSize );
        mGridMesh->vertex( (float)xVal, 0, (float)zSize );
    }// end for each x dir line
    
    // Add z lines.
    for( int zVal = -zSize; zVal < zMax; zVal += spacing ) {
        mGridMesh->color( defaultColor );
        mGridMesh->vertex( (float)xSize, 0, (float)zVal );
        mGridMesh->vertex( (float)-xSize, 0, (float)zVal );
    }// end for each z dir line
}


//------------------ RENDER THE SCENE ------------------------

void CCLfixedApp::renderScene()
{
    
    gl::pushMatrices();
    mGridMesh->draw();
    gl::popMatrices();
}

//-------------------- IMPORT DATA -------------------------

void CCLfixedApp::initData()
{
    
    /********** DATA ____ GUI ***********************/
    
    //CCL_MocapData("CCL_JOINT_CCL3_00_skip10.json", jointList);
//    
//    /********** DATA ____ GUI ***********************/
//    jointList = CCL_MocapData::loadMotionCaptureFromJson(getAssetPath("CCL_JOINT_CCL3_00_skip10.json"));
//    
//    //CREATE AND INITIALISE A CCL_MOCAPDATA OBJECT, PASSING IN THE GLOBAL "jointList" AS A REFERENCE
//    //-->   jointList = ccl::loadMotionCaptureFromJson(getAssetPath("CCL_JOINT.json"));
//   // jointList = ccl::loadMotionCaptureFromJson(getAssetPath("CCL_JOINT_CCL4_00.json"));
//    //  jointList = ccl::loadMotionCaptureFromSite(Url(ccl::URL_STREAM_JSON), 1);
//    //    CCL_MocapData(1, jointList); //UNCOMMENT THIS LINE TO CAPTURE NEW JSON DATA
//    std::cout << jointList.size()<< endl;
//    std::cout << endl;
//    std::cout << endl;
//    std::cout << endl;
    
    //CREATE AND INITIALISE A CCL_MOCAPDATA OBJECT, PASSING IN THE GLOBAL "jointList" AS A REFERENCE
    /********** DATA ____ GUI ***********************/
    
    CCL_MocapData("CCL_JOINT_CCL3_00_skip10.json", jointList);
    /********** DATA ____ GUI ***********************/
    
    //    CCL_MocapData(1, jointList);
    // CCL_MocapData("CCL_JOINT_CCL4_00",jointList);
    std::cout << jointList.size()<< endl;
    std::cout << endl;
    std::cout << endl;
    std::cout << endl;
    
    CCL_Dancer("CCL_JOINT_CCL3_00_skip10.json", 10, 120);
    
    
}

//--------------------- SETUP SHADERS -----------------------

void CCLfixedApp::setupShader(){
    
    //CHOOSE BETWEEN solidShader AND mGlsl AS SHADERS FOR THE SPHERES
    solidShader = gl::getStockShader( gl::ShaderDef().color() );
    mGlsl = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );
    mSphereBatch = gl::Batch::create( geom::Sphere(), mGlsl );
}



//------------------------ DISTORT LIMBS ---------------------------------

std::vector<glm::vec3> CCLfixedApp::distortLimbs(const std::vector<vec3> &normalLimbs, float scaleFactor){
    
    std::vector<glm::vec3> distortedVectors = normalLimbs;
    
    glm::vec3 foreArmDirection = normalLimbs[8] - normalLimbs[9];
    float forearm = distance(normalLimbs[9], normalLimbs[8]);
    glm::vec3 newArm = normalize(foreArmDirection);
    glm::vec3 newWrist = normalLimbs[8] + newArm;
    
    distortedVectors[8] = newWrist*2.0f;
    
    return distortedVectors;
}

//-------------------------UPDATE RIBBONS--------------------------------

void CCLfixedApp::updateRibbons()
{
    auto easing = 1.0f;
    int i = 0;
    for (auto &r:ribbons)
    {
        auto target = framePositions[i];
        const auto no_data_value = -123456;
        if (glm::all(glm::greaterThan(target, vec3(no_data_value))))
        {
            r._target = target;
        }
        
        auto &points = r._spine;
        for (auto i = points.size() - 1; i > 0; i -= 1)
        {
            auto &p1 = points.at(i);
            auto &p2 = points.at(i - 1);
            p1 += (p2 - p1) * easing;
        }
        auto &point = points.at(0);
        point += (r._target - point) * easing;
        i++;
    }
    
    for (auto &r: ribbons)
    {
        r._triangles = sansumbrella::createRibbon(20.0f, ci::EaseInOutQuad(), mCamera.getEyePoint(), r._spine);
    }
    
    //  _camera.lookAt(currentJointPosition(0));
}


//--------------------- DRAW RIBBONS ---------------------------------

void CCLfixedApp::drawRibbons(){
    for (auto &ribbon: ribbons)
    {
        gl::enableAlphaBlending();
        ColorA moop(1.0,1.0,1.,0.4);
        gl::begin(GL_TRIANGLE_STRIP);
        for (auto &p : ribbon._triangles)
        {
            gl::vertex(p);
        }
        gl::end();
    }
}

//----------------------LOAD DANCERS --------------------------------

void CCLfixedApp::loadDancers(){
    vector<std::string> dataVector = {"CCL_JOINT_CCL3_00_skip10.json",
        "CCL_JOINT_CCL4_00_skip4.json",
        "CCL_JOINT_CCL4_01_skip4.json",
        "CCL_JOINT_CCL4_02_skip4.json",
        "CCL_JOINT_CCL4_03_skip8.json",
        "CCL_JOINT_CCL4_04_skip8.json"};
    
    CCL_Dancer dancer1 = CCL_Dancer(dataVector[0], 10, 120);
    CCL_Dancer dancer2 = CCL_Dancer(dataVector[1], 4, 240);
    CCL_Dancer dancer3 = CCL_Dancer(dataVector[2], 4, 240);
    CCL_Dancer dancer4 = CCL_Dancer(dataVector[3], 4, 240);
    CCL_Dancer dancer5 = CCL_Dancer(dataVector[4], 8, 240);
    CCL_Dancer dancer6 = CCL_Dancer(dataVector[5], 8, 240);
    
    dancers.push_back(dancer1);
    dancers.push_back(dancer2);
    dancers.push_back(dancer3);
    dancers.push_back(dancer4);
    dancers.push_back(dancer5);
    dancers.push_back(dancer6);
    
}

CINDER_APP( CCLfixedApp, RendererGl(RendererGl::Options().msaa( 16 ) ), [&]( App::Settings *settings ) {
    settings->setWindowSize( 1280, 720 );
    
} )
