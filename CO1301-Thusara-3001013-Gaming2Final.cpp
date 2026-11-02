// CO1301-Thusara-3001013-Gaming2Final.cpp: A program using the TL-Engine
// Thusara Dinusith
// Milestone 4(85%+) - First Class Level

#include <TL-Engine.h>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace tle;
using namespace std;

const float kPi = 3.14159265f;

const float kCameraMoveSpeed = 25.0f;
const float kCameraTurnSpeed = 0.08f;
const float kCameraPitchMin = -15.0f;
const float kCameraPitchMax = 30.0f;

const float kTurnSpeed = 70.0f;
const float kForwardThrust = 38.0f;
const float kReverseThrust = 19.0f;
const float kDrag = 1.8f;
const float kMaxSpeed = 42.0f;

const float kBoostMultiplier = 1.4f;
const float kBoostMaxTime = 3.0f;
const float kBoostCooldownTime = 10.0f;
const float kOverheatDragMultiplier = 2.0f;

const float kCarRadius = 1.5f;
const float kTankRadius = 2.5f;
const float kCheckpointPostRadius = 3.0f;

const float kBarrierBounce = 0.65f;
const float kTankBounce = 0.30f;
const float kNpcBounce = 0.35f;

const int kMaxHealth = 100;
const int kBoostDisabledHealth = 20;
const int kTotalLaps = 2;

const float kDamageCooldownTime = 0.35f;

const float kHoverBaseY = 5.0f;
const float kHoverAmplitude = 0.35f;
const float kHoverFrequency = 4.0f;
const float kLeanAmount = 10.0f;
const float kPitchAmount = 5.0f;
const float kPitchSmoothSpeed = 6.0f;

const float kCheckpointHalfWidth = 7.0f;
const float kCheckpointHalfDepth = 11.0f;
const float kCheckpointPostOffset = 8.5f;

const float kNpcSpeed = 19.0f;
const float kNpcTurnSpeed = 90.0f;

const float kMetresPerUnit = 0.25f;
const float kCrossLifeTime = 3.0f;

const float kNoTimeRemaining = 0.0f;
const int kStartIndex = 0;
const int kStepOne = 1;

const int kFirstCharacterIndex = 0;
const float kCountdownSecond = 1.0f;
const char kCommentMarker = '#';

const char* kCountdownThreeText = "3";
const char* kCountdownTwoText = "2";
const char* kCountdownOneText = "1";
const char* kCameraInstructionText = "1 = Chase Cam   2 = First Person   R = Restart";
const char* kSkyboxMeshFile = "Skybox 07.x";

const float kDegreesNinety = 90.0f;
const float kDegreesTwoSeventy = 270.0f;
const float kRotationTolerance = 0.1f;
const float kDegreesToRadians = kPi / 180.0f;
const float kDegreesHalfTurn = 180.0f;
const float kDegreesFullTurn = 360.0f;
const float kBoostWarningTime = 2.0f;
const float kCheckpointBounce = 0.25f;
const float kKmhConversion = 3.6f;

const float kPlayerStartX = 0.0f;
const float kPlayerStartZ = -15.0f;
const float kPlayerStartRotY = 0.0f;
const float kNpcStartX = 4.0f;
const float kNpcStartZ = -15.0f;
const float kGroundY = -1.0f;
const float kSkyY = -750.0f;
const float kHiddenY = -100.0f;

const float kCarScale = 0.6f;
const float kNpcCarScale = 0.6f;
const float kCheckpointScale = 1.35f;
const float kIsleScale = 1.4f;
const float kWallScale = 1.6f;
const float kTankScale = 1.15f;
const float kGarageScale = 4.0f;
const float kTribuneScale = 6.0f;

const float kChaseCameraStartX = 0.0f;
const float kChaseCameraStartY = 8.0f;
const float kChaseCameraStartZ = -14.0f;
const float kChaseCameraStartYaw = 0.0f;
const float kChaseCameraStartPitch = 15.0f;
const float kFirstPersonForwardOffset = 2.5f;
const float kFirstPersonHeightOffset = 3.5f;

const float kWallHalfWidth = 3.5f;
const float kWallHalfDepth = 8.5f;
const float kIsleHalfWidth = 3.5f;
const float kIsleHalfDepth = 3.5f;

const int kSmokeCount = 60;
const float kSmokeScale = 0.15f;
const float kSmokeActivationHealth = 40.0f;
const float kSmokeSpawnInterval = 0.03f;
const float kSmokeLifeTime = 2.0f;
const float kSmokeBackOffset = 2.0f;
const float kSmokeHeightOffset = 1.2f;
const float kSmokeRandomRange = 10.0f;
const float kSmokeRandomOffset = 5.0f;
const float kSmokePositionRandomScale = 0.1f;
const float kSmokeRiseSpeed = 1.5f;
const float kSmokeDriftScale = 0.15f;

const int kUiBottomOffset = 120;
const int kUiColumnOneX = 20;
const int kUiColumnTwoX = 240;
const int kUiColumnThreeX = 480;
const int kUiColumnFourX = 850;
const int kUiLineOneOffset = 10;
const int kUiLineTwoOffset = 35;
const int kUiLineThreeOffset = 60;
const int kUiLineFourOffset = 70;
const int kUiStageOffset = 45;
const int kUiWinnerXOffset = 120;
const int kUiGameOverXOffset = 90;
const int kUiTopMessageY = 40;
const int kTimePrecision = 2;
const int kCooldownPrecision = 1;

const float kCrossY = 0.2f;
const float kNpcWaypointReachDistance = 4.0f;
const int kRaceCompetitorCount = 2;
const float kCheckpointModelY = 0.0f;
const float kSceneryModelY = 0.0f;
const float kModelResetX = 0.0f;
const float kModelResetZ = 0.0f;


// Stores X and Z positions
struct Vec2
{
    float x;
    float z;
};

struct CheckpointData
{
    IModel* model;
    float x;
    float z;
    float rotY;
};

struct CrossData
{
    IModel* model;
    float timer;
};

struct SceneItem
{
    string type;
    float x;
    float z;
    float rotY;
};

enum EGameState
{
    WaitingToStart,
    Countdown3,
    Countdown2,
    Countdown1,
    GoState,
    Racing,
    RaceComplete,
    GameOver
};

enum ECameraMode
{
    ChaseCam,
    FirstPersonCam
};

Vec2 AddVec(const Vec2& firstVector, const Vec2& secondVector)
{
    Vec2 result;
    result.x = firstVector.x + secondVector.x;
    result.z = firstVector.z + secondVector.z;
    return result;
}


Vec2 SubVec(const Vec2& firstVector, const Vec2& secondVector)
{
    Vec2 result;
    result.x = firstVector.x - secondVector.x;
    result.z = firstVector.z - secondVector.z;
    return result;
}

Vec2 MulVec(const Vec2& vectorValue, float scaleAmount)
{
    Vec2 result;
    result.x = vectorValue.x * scaleAmount;
    result.z = vectorValue.z * scaleAmount;
    return result;
}

float LengthVec(const Vec2& vectorValue)
{
    return sqrt(vectorValue.x * vectorValue.x + vectorValue.z * vectorValue.z);
}

Vec2 NormaliseVec(const Vec2& vectorValue)
{
    float vectorLength = LengthVec(vectorValue);

    if (vectorLength == kNoTimeRemaining)
    {
        Vec2 zeroVector = { kNoTimeRemaining, kNoTimeRemaining };
        return zeroVector;
    }

    Vec2 result;
    result.x = vectorValue.x / vectorLength;
    result.z = vectorValue.z / vectorLength;
    return result;
}

float Distance2D(float firstPointX, float firstPointZ, float secondPointX, float secondPointZ)
{
    float distanceX = firstPointX - secondPointX;
    float distanceZ = firstPointZ - secondPointZ;
    return sqrt(distanceX * distanceX + distanceZ * distanceZ);
}

float ClampFloat(float value, float minValue, float maxValue)
{
    if (value < minValue) return minValue;
    if (value > maxValue) return maxValue;
    return value;
}


bool SphereToSphere(
    float firstObjectX, float firstObjectZ, float firstObjectRadius,
    float secondObjectX, float secondObjectZ, float secondObjectRadius)
{
    float distanceX = firstObjectX - secondObjectX;
    float distanceZ = firstObjectZ - secondObjectZ;
    float distanceSquared = distanceX * distanceX + distanceZ * distanceZ;
    float combinedRadius = firstObjectRadius + secondObjectRadius;
    return distanceSquared < combinedRadius * combinedRadius;
}


bool PointInCheckpointGap(float pointX, float pointZ, const CheckpointData& checkpoint)
{
    float localX = pointX - checkpoint.x;
    float localZ = pointZ - checkpoint.z;

    if (fabs(checkpoint.rotY - kDegreesNinety) < kRotationTolerance)
    {
        return fabs(localX) < kCheckpointHalfDepth && fabs(localZ) < kCheckpointHalfWidth;
    }
    else
    {
        return fabs(localX) < kCheckpointHalfWidth && fabs(localZ) < kCheckpointHalfDepth;
    }
}

// Checks if the car hits checkpoint posts
bool CheckCheckpointPostCollision(float carX, float carZ, const CheckpointData& checkpoint)
{
    float leftX = checkpoint.x;
    float leftZ = checkpoint.z;
    float rightX = checkpoint.x;
    float rightZ = checkpoint.z;

    if (fabs(checkpoint.rotY - kDegreesNinety) < kRotationTolerance)
    {
        leftZ = checkpoint.z - kCheckpointPostOffset;
        rightZ = checkpoint.z + kCheckpointPostOffset;
    }
    else
    {
        leftX = checkpoint.x - kCheckpointPostOffset;
        rightX = checkpoint.x + kCheckpointPostOffset;
    }

    bool hitLeft = SphereToSphere(carX, carZ, kCarRadius, leftX, leftZ, kCheckpointPostRadius);
    bool hitRight = SphereToSphere(carX, carZ, kCarRadius, rightX, rightZ, kCheckpointPostRadius);

    return hitLeft || hitRight;
}

// Reduces player health after a collision
void DamagePlayer(int& health, float& damageCooldown)
{
    if (damageCooldown <= kNoTimeRemaining)
    {
        health -= kStepOne;
        damageCooldown = kDamageCooldownTime;
    }
}

void ResetChaseCamera(float& camOffsetX, float& camOffsetY, float& camOffsetZ, float& cameraYaw, float& cameraPitch)
{
    camOffsetX = kChaseCameraStartX;
    camOffsetY = kChaseCameraStartY;
    camOffsetZ = kChaseCameraStartZ;
    cameraYaw = kChaseCameraStartYaw;
    cameraPitch = kChaseCameraStartPitch;
}

void ResetPlayer(IModel* car, float& carRotY, Vec2& velocity)
{
    car->SetPosition(kPlayerStartX, kHoverBaseY, kPlayerStartZ);
    car->ResetOrientation();
    carRotY = kPlayerStartRotY;
    velocity.x = kNoTimeRemaining;
    velocity.z = kNoTimeRemaining;
}

void ResetNPC(IModel* npcCar, float& npcRotY, int& npcWaypoint, Vec2& npcVelocity)
{
    npcCar->SetPosition(kNpcStartX, kHoverBaseY, kNpcStartZ);
    npcCar->ResetOrientation();
    npcRotY = kNoTimeRemaining;
    npcWaypoint = kStartIndex;
    npcVelocity.x = kNoTimeRemaining;
    npcVelocity.z = kNoTimeRemaining;
}

void ApplyCarVisuals(IModel* car, float rotY, float leanAngle, float pitchAngle)
{
    float carX = car->GetX();
    float carY = car->GetY();
    float carZ = car->GetZ();

    car->ResetOrientation();
    car->SetPosition(carX, carY, carZ);
    car->RotateY(rotY);
    car->RotateLocalZ(leanAngle);
    car->RotateLocalX(pitchAngle);
}

void ShowCross(CrossData& cross, float crossX, float crossZ)
{
    cross.model->SetPosition(crossX, kCrossY, crossZ);
    cross.timer = kCrossLifeTime;
}

void UpdateCrosses(vector<CrossData>& crosses, float frameTime)
{
    for (int crossIndex = kStartIndex; crossIndex < (int)crosses.size(); crossIndex++)
    {
        if (crosses[crossIndex].timer > kNoTimeRemaining)
        {
            crosses[crossIndex].timer -= frameTime;

            if (crosses[crossIndex].timer <= kNoTimeRemaining)
            {
                crosses[crossIndex].timer = kNoTimeRemaining;
                crosses[crossIndex].model->SetPosition(crosses[crossIndex].model->GetX(), kHiddenY, crosses[crossIndex].model->GetZ());
            }
        }
    }
}

int GetProgressScore(int lap, int nextCheckpoint, int totalCheckpoints)
{
    return (lap - kStepOne) * totalCheckpoints + nextCheckpoint;
}

float GetSpeedKmh(const Vec2& velocity)
{
    float metresPerSecond = LengthVec(velocity) * kMetresPerUnit;
    return metresPerSecond * kKmhConversion;
}

bool SphereToBox(
    float objectX, float objectZ, float objectRadius,
    float boxCenterX, float boxCenterZ, float boxHalfWidth, float boxHalfDepth)
{
    float closestX = ClampFloat(objectX, boxCenterX - boxHalfWidth, boxCenterX + boxHalfWidth);
    float closestZ = ClampFloat(objectZ, boxCenterZ - boxHalfDepth, boxCenterZ + boxHalfDepth);

    float distanceX = objectX - closestX;
    float distanceZ = objectZ - closestZ;

    return (distanceX * distanceX + distanceZ * distanceZ) < (objectRadius * objectRadius);
}

bool HitBarrierAtPosition(float testPositionX, float testPositionZ,
    const vector<IModel*>& wallModels,
    const vector<IModel*>& isleModels,
    const vector<IModel*>& hiddenWallModels,
    const vector<float>& wallRotations,
    const vector<float>& isleRotations,
    const vector<float>& hiddenWallRotations)
{
    for (int hiddenWallIndex = kStartIndex; hiddenWallIndex < (int)hiddenWallModels.size(); hiddenWallIndex++)
    {
        float barrierHalfWidth = kWallHalfWidth;
        float barrierHalfDepth = kWallHalfDepth;

        if (hiddenWallIndex < (int)hiddenWallRotations.size())
        {
            if (fabs(hiddenWallRotations[hiddenWallIndex] - kDegreesNinety) < kRotationTolerance ||
                fabs(hiddenWallRotations[hiddenWallIndex] - kDegreesTwoSeventy) < kRotationTolerance)
            {
                float originalHalfWidth = barrierHalfWidth;
                barrierHalfWidth = barrierHalfDepth;
                barrierHalfDepth = originalHalfWidth;
            }
        }

        if (SphereToBox(testPositionX, testPositionZ, kCarRadius,
            hiddenWallModels[hiddenWallIndex]->GetX(), hiddenWallModels[hiddenWallIndex]->GetZ(),
            barrierHalfWidth, barrierHalfDepth))
        {
            return true;
        }
    }

    for (int wallIndex = kStartIndex; wallIndex < (int)wallModels.size(); wallIndex++)
    {
        float barrierHalfWidth = kWallHalfWidth;
        float barrierHalfDepth = kWallHalfDepth;

        if (wallIndex < (int)wallRotations.size())
        {
            if (fabs(wallRotations[wallIndex] - kDegreesNinety) < kRotationTolerance ||
                fabs(wallRotations[wallIndex] - kDegreesTwoSeventy) < kRotationTolerance)
            {
                float originalHalfWidth = barrierHalfWidth;
                barrierHalfWidth = barrierHalfDepth;
                barrierHalfDepth = originalHalfWidth;
            }
        }

        if (SphereToBox(testPositionX, testPositionZ, kCarRadius,
            wallModels[wallIndex]->GetX(), wallModels[wallIndex]->GetZ(),
            barrierHalfWidth, barrierHalfDepth))
        {
            return true;
        }
    }

    for (int isleIndex = kStartIndex; isleIndex < (int)isleModels.size(); isleIndex++)
    {
        float barrierHalfWidth = kIsleHalfWidth;
        float barrierHalfDepth = kIsleHalfDepth;

        if (isleIndex < (int)isleRotations.size())
        {
            if (fabs(isleRotations[isleIndex] - kDegreesNinety) < kRotationTolerance ||
                fabs(isleRotations[isleIndex] - kDegreesTwoSeventy) < kRotationTolerance)
            {
                float originalHalfWidth = barrierHalfWidth;
                barrierHalfWidth = barrierHalfDepth;
                barrierHalfDepth = originalHalfWidth;
            }
        }

        if (SphereToBox(testPositionX, testPositionZ, kCarRadius,
            isleModels[isleIndex]->GetX(), isleModels[isleIndex]->GetZ(),
            barrierHalfWidth, barrierHalfDepth))
        {
            return true;
        }
    }

    return false;
}

bool LoadSceneFile(const string& fileName, vector<SceneItem>& sceneItems)
{
    ifstream file(fileName.c_str());

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (getline(file, line))
    {
        if (line == "") continue;
        if (line[kFirstCharacterIndex] == kCommentMarker) continue;

        stringstream ss(line);
        SceneItem item;
        ss >> item.type >> item.x >> item.z >> item.rotY;

        if (!ss.fail())
        {
            sceneItems.push_back(item);
        }
    }

    file.close();
    return true;
}

bool LoadWaypointsFile(const string& fileName, vector<Vec2>& waypoints)
{
    ifstream file(fileName.c_str());

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (getline(file, line))
    {
        if (line == "") continue;
        if (line[kFirstCharacterIndex] == kCommentMarker) continue;

        stringstream ss(line);
        Vec2 point;
        ss >> point.x >> point.z;

        if (!ss.fail())
        {
            waypoints.push_back(point);
        }
    }

    file.close();
    return true;
}

// Updates first-person camera
void UpdateFirstPersonCamera(ICamera* camera, IModel* car, float carRotY)
{
    float angle = carRotY * kDegreesToRadians;

    float offsetX = sin(angle) * kFirstPersonForwardOffset;
    float offsetZ = cos(angle) * kFirstPersonForwardOffset;

    camera->SetPosition(car->GetX() + offsetX,
        car->GetY() + kFirstPersonHeightOffset,
        car->GetZ() + offsetZ);

    camera->ResetOrientation();
    camera->RotateY(carRotY);
}

//chase camera
void UpdateChaseCamera(I3DEngine* engine, ICamera* camera, IModel* car, float carRotY,
    float& camOffsetX, float& camOffsetY, float& camOffsetZ,
    float& cameraYaw, float& cameraPitch, float frameTime)
{
    if (engine->KeyHeld(Key_Up))    camOffsetZ += kCameraMoveSpeed * frameTime;
    if (engine->KeyHeld(Key_Down))  camOffsetZ -= kCameraMoveSpeed * frameTime;
    if (engine->KeyHeld(Key_Left))  camOffsetX -= kCameraMoveSpeed * frameTime;
    if (engine->KeyHeld(Key_Right)) camOffsetX += kCameraMoveSpeed * frameTime;

    cameraYaw += engine->GetMouseMovementX() * kCameraTurnSpeed;
    cameraPitch -= engine->GetMouseMovementY() * kCameraTurnSpeed;
    cameraPitch = ClampFloat(cameraPitch, kCameraPitchMin, kCameraPitchMax);

    float totalYaw = carRotY + cameraYaw;
    float angle = totalYaw * kDegreesToRadians;

    float behindX = sin(angle) * camOffsetZ;
    float behindZ = cos(angle) * camOffsetZ;
    float sideX = cos(angle) * camOffsetX;
    float sideZ = -sin(angle) * camOffsetX;

    float px = car->GetX() + behindX + sideX;
    float py = car->GetY() + camOffsetY;
    float pz = car->GetZ() + behindZ + sideZ;

    camera->SetPosition(px, py, pz);
    camera->ResetOrientation();
    camera->RotateY(totalYaw);
    camera->RotateLocalX(cameraPitch);
}

// Moves NPC towards waypoints
void UpdateNPC(IModel* npcCar, float& npcRotY, Vec2& npcVelocity,
    const vector<Vec2>& waypoints, int& npcWaypoint, float frameTime)
{
    if (waypoints.empty())
    {
        return;
    }

    Vec2 npcPosition = { npcCar->GetX(), npcCar->GetZ() };
    Vec2 targetWaypoint = waypoints[npcWaypoint];

    Vec2 directionToTarget = SubVec(targetWaypoint, npcPosition);
    Vec2 normalisedDirection = NormaliseVec(directionToTarget);

    float wantedAngle = atan2(normalisedDirection.x, normalisedDirection.z) / kDegreesToRadians;
    float angleDifference = wantedAngle - npcRotY;

    while (angleDifference > kDegreesHalfTurn) angleDifference -= kDegreesFullTurn;
    while (angleDifference < -kDegreesHalfTurn) angleDifference += kDegreesFullTurn;

    if (angleDifference > kNpcTurnSpeed * frameTime) angleDifference = kNpcTurnSpeed * frameTime;
    if (angleDifference < -kNpcTurnSpeed * frameTime) angleDifference = -kNpcTurnSpeed * frameTime;

    npcRotY += angleDifference;

    float angle = npcRotY * kDegreesToRadians;
    Vec2 forwardDirection = { sin(angle), cos(angle) };

    npcVelocity = MulVec(forwardDirection, kNpcSpeed);

    npcCar->SetPosition(
        npcCar->GetX() + npcVelocity.x * frameTime,
        npcCar->GetY(),
        npcCar->GetZ() + npcVelocity.z * frameTime
    );

    ApplyCarVisuals(npcCar, npcRotY, kNoTimeRemaining, kNoTimeRemaining);

    if (Distance2D(npcCar->GetX(), npcCar->GetZ(), targetWaypoint.x, targetWaypoint.z) < kNpcWaypointReachDistance)
    {
        npcWaypoint++;

        if (npcWaypoint >= (int)waypoints.size())
        {
            npcWaypoint = kStartIndex;
        }
    }
}


void DrawUI(IFont* font, I3DEngine* engine, EGameState gameState, const string& stageMsg,
    float playerTime, int health, int lap, int totalLaps, int checkpointNumber, int totalCheckpoints,
    bool boostReady, bool isBoosting, bool boostOverheated, float boostTimer, float boostCooldownTimer,
    int racePosition, const string& winnerText, const Vec2& velocity)
{
    ostringstream timeSS;
    timeSS << fixed << setprecision(kTimePrecision) << playerTime;

    ostringstream coolSS;
    coolSS << fixed << setprecision(kCooldownPrecision) << boostCooldownTimer;

    int uiY = engine->GetHeight() - kUiBottomOffset;

    font->Draw("Time: " + timeSS.str(), kUiColumnOneX, uiY + kUiLineOneOffset, kWhite);
    font->Draw("Health: " + to_string(health), kUiColumnOneX, uiY + kUiLineTwoOffset, kWhite);
    int shownLap = lap;
    if (shownLap > totalLaps) shownLap = totalLaps;

    font->Draw("Lap: " + to_string(shownLap) + " / " + to_string(totalLaps), kUiColumnOneX, uiY + kUiLineThreeOffset, kWhite);

    font->Draw("Checkpoint: " + to_string(checkpointNumber) + " / " + to_string(totalCheckpoints), kUiColumnTwoX, uiY + kUiLineOneOffset, kWhite);
    font->Draw("Speed: " + to_string((int)GetSpeedKmh(velocity)) + " km/h", kUiColumnTwoX, uiY + kUiLineTwoOffset, kWhite);
    font->Draw("Position: " + to_string(racePosition) + " / " + to_string(kRaceCompetitorCount), kUiColumnTwoX, uiY + kUiLineThreeOffset, kWhite);

    font->Draw(kCameraInstructionText, kUiColumnThreeX, uiY + kUiLineOneOffset, kWhite);
    font->Draw(stageMsg, kUiColumnThreeX, uiY + kUiStageOffset, kBlue);

    if (health < kBoostDisabledHealth)
    {
        font->Draw("Boost disabled: low health", kUiColumnThreeX, uiY + kUiLineFourOffset, kRed);
    }
    else if (boostOverheated)
    {
        font->Draw("Boost overheated", kUiColumnFourX, uiY + kUiLineOneOffset, kRed);
        font->Draw("Cooldown: " + coolSS.str(), kUiColumnFourX, uiY + kUiLineTwoOffset, kWhite);
    }
    else if (isBoosting)
    {
        font->Draw("BOOST ACTIVE", kUiColumnFourX, uiY + kUiLineOneOffset, kGreen);

        if (boostTimer >= kBoostWarningTime)
        {
            font->Draw("Warning: overheating", kUiColumnFourX, uiY + kUiLineTwoOffset, kRed);
        }
    }
    else if (boostReady)
    {
        font->Draw("Boost ready", kUiColumnFourX, uiY + kUiLineOneOffset, kGreen);
    }

    if (gameState == RaceComplete)
    {
        font->Draw(winnerText, engine->GetWidth() / kRaceCompetitorCount - kUiWinnerXOffset, kUiTopMessageY, kYellow);
    }

    if (gameState == GameOver)
    {
        font->Draw("GAME OVER", engine->GetWidth() / kRaceCompetitorCount - kUiGameOverXOffset, kUiTopMessageY, kRed);
    }
}

void main()
{
    I3DEngine* engine = New3DEngine(kTLX);
    engine->StartWindowed();

    engine->AddMediaFolder(".\\media");

    IMesh* carMesh = engine->LoadMesh("race2.x");
    IMesh* checkpointMesh = engine->LoadMesh("Checkpoint.x");
    IMesh* isleMesh = engine->LoadMesh("IsleStraight.x");
    IMesh* wallMesh = engine->LoadMesh("Wall.x");
    IMesh* groundMesh = engine->LoadMesh("ground.x");
    IMesh* skyMesh = engine->LoadMesh(kSkyboxMeshFile);
    IMesh* tankMesh1 = engine->LoadMesh("TankSmall1.x");
    IMesh* tankMesh2 = engine->LoadMesh("TankSmall2.x");
    IMesh* crossMesh = engine->LoadMesh("Cross.x");
    IMesh* GarageMesh = engine->LoadMesh("GarageLarge.x");
    IMesh* TribuneMesh = engine->LoadMesh("Tribune3.x");
    IMesh* smokeMesh = engine->LoadMesh("Flare.x");

    IModel* ground = groundMesh->CreateModel(kModelResetX, kGroundY, kModelResetZ);

    IModel* sky = skyMesh->CreateModel(kModelResetX, kSkyY, kModelResetZ);

    IModel* car = carMesh->CreateModel(kPlayerStartX, kHoverBaseY, kPlayerStartZ);
    car->Scale(kCarScale);

    IModel* npcCar = carMesh->CreateModel(kNpcStartX, kHoverBaseY, kNpcStartZ);
    npcCar->Scale(kNpcCarScale);
    npcCar->SetSkin("td_interstellar.jpg");

    vector<IModel*> isleModels;
    vector<float> isleRotations;

    vector<IModel*> GarageModels;
    vector<IModel*> wallModels;
    vector<float> wallRotations;
    vector<IModel*> TribuneModels;
    vector<IModel*> tankModels;
    vector<CheckpointData> checkpoints;
    vector<CrossData> checkpointCrosses;
    vector<IModel*> smokeModels;
    vector<float> smokeTimers;
    vector<IModel*> hiddenWallModels;
    vector<float> hiddenWallRotations;

    for (int smokeCreateIndex = kStartIndex; smokeCreateIndex < kSmokeCount; smokeCreateIndex++)
    {
        IModel* smoke = smokeMesh->CreateModel(kModelResetX, kHiddenY, kModelResetZ);
        smoke->Scale(kSmokeScale);
        smoke->SetSkin("Grating3.tga");
        smokeModels.push_back(smoke);
        smokeTimers.push_back(kNoTimeRemaining);
    }

    vector<SceneItem> sceneItems;
    bool sceneLoaded = LoadSceneFile(".\\media\\scene.txt", sceneItems);

    if (!sceneLoaded || sceneItems.empty())
    {
        engine->Delete();
        return;
    }

    for (int sceneItemIndex = kStartIndex; sceneItemIndex < (int)sceneItems.size(); sceneItemIndex++)
    {
        SceneItem item = sceneItems[sceneItemIndex];

        if (item.type == "Checkpoint")
        {
            IModel* model = checkpointMesh->CreateModel(item.x, kCheckpointModelY, item.z);
            model->RotateY(item.rotY);
            model->Scale(kCheckpointScale);

            CheckpointData checkpoint;
            checkpoint.model = model;
            checkpoint.x = item.x;
            checkpoint.z = item.z;
            checkpoint.rotY = item.rotY;
            checkpoints.push_back(checkpoint);

            CrossData cross;
            cross.model = crossMesh->CreateModel(item.x, kHiddenY, item.z);
            cross.timer = kNoTimeRemaining;
            checkpointCrosses.push_back(cross);
        }
        else if (item.type == "Isle")
        {
            IModel* model = isleMesh->CreateModel(item.x, kSceneryModelY, item.z);
            model->RotateY(item.rotY);
            model->Scale(kIsleScale);
            isleModels.push_back(model);
            isleRotations.push_back(item.rotY);
        }
        else if (item.type == "Wall")
        {
            IModel* model = wallMesh->CreateModel(item.x, kSceneryModelY, item.z);
            model->RotateY(item.rotY);
            model->Scale(kWallScale);
            wallModels.push_back(model);
            wallRotations.push_back(item.rotY);
        }
        else if (item.type == "HiddenWall")
        {
            IModel* model = wallMesh->CreateModel(item.x, kSceneryModelY, item.z);
            model->RotateY(item.rotY);
            model->Scale(kWallScale);

            model->SetPosition(item.x, kHiddenY, item.z);

            hiddenWallModels.push_back(model);
            hiddenWallRotations.push_back(item.rotY);
        }
        else if (item.type == "Tank1")
        {
            IModel* model = tankMesh1->CreateModel(item.x, kSceneryModelY, item.z);
            model->RotateY(item.rotY);
            model->Scale(kTankScale);
            tankModels.push_back(model);
        }
        else if (item.type == "Tank2")
        {
            IModel* model = tankMesh2->CreateModel(item.x, kSceneryModelY, item.z);
            model->RotateY(item.rotY);
            model->Scale(kTankScale);
            tankModels.push_back(model);
        }
        else if (item.type == "Garage")
        {
            IModel* model = GarageMesh->CreateModel(item.x, kSceneryModelY, item.z);
            model->RotateY(item.rotY);
            model->Scale(kGarageScale);
            GarageModels.push_back(model);
        }
        else if (item.type == "Tribune")
        {
            IModel* model = TribuneMesh->CreateModel(item.x, kSceneryModelY, item.z);
            model->RotateY(item.rotY);
            model->Scale(kTribuneScale);
            TribuneModels.push_back(model);
        }
    }

    vector<Vec2> npcWaypoints;
    LoadWaypointsFile(".\\media\\waypoints.txt", npcWaypoints);

    ICamera* camera = engine->CreateCamera(kManual);
    IFont* font = engine->DefaultFont();

    ECameraMode cameraMode = ChaseCam;
    EGameState gameState = WaitingToStart;

    float camOffsetX;
    float camOffsetY;
    float camOffsetZ;
    float cameraYaw;
    float cameraPitch;
    ResetChaseCamera(camOffsetX, camOffsetY, camOffsetZ, cameraYaw, cameraPitch);

    string stageMsg = "Hit Space to Start";
    string winnerText = "";

    float countdownTimer = kNoTimeRemaining;
    float playerTime = kNoTimeRemaining;
    float npcTime = kNoTimeRemaining;

    int health = kMaxHealth;
    float damageCooldown = kNoTimeRemaining;

    float carRotY = kPlayerStartRotY;
    Vec2 velocity = { kNoTimeRemaining, kNoTimeRemaining };

    float npcRotY = kNoTimeRemaining;
    Vec2 npcVelocity = { kNoTimeRemaining, kNoTimeRemaining };
    int npcWaypoint = kStartIndex;

    int nextCheckpoint = kStartIndex;
    int npcNextCheckpoint = kStartIndex;
    int playerLap = kStepOne;
    int npcLap = kStepOne;

    bool boostReady = true;
    bool isBoosting = false;
    bool boostOverheated = false;
    float boostTimer = kNoTimeRemaining;
    float boostCooldownTimer = kNoTimeRemaining;

    float pitchAngle = kNoTimeRemaining;
    float targetPitchAngle = kNoTimeRemaining;
    float smokeSpawnTimer = kNoTimeRemaining;

   
    while (engine->IsRunning())
    {
        engine->DrawScene();
        float frameTime = engine->Timer();

        if (damageCooldown > kNoTimeRemaining)
        {
            damageCooldown -= frameTime;
        }

        float hoverY = kHoverBaseY + sin(playerTime * kHoverFrequency) * kHoverAmplitude;
        float npcHoverY = kHoverBaseY + sin(npcTime * kHoverFrequency) * kHoverAmplitude;

        UpdateCrosses(checkpointCrosses, frameTime);

        if (engine->KeyHit(Key_R))
        {
            ResetPlayer(car, carRotY, velocity);
            ResetNPC(npcCar, npcRotY, npcWaypoint, npcVelocity);
            ResetChaseCamera(camOffsetX, camOffsetY, camOffsetZ, cameraYaw, cameraPitch);

            for (int checkpointCrossIndex = kStartIndex; checkpointCrossIndex < (int)checkpointCrosses.size(); checkpointCrossIndex++)
            {
                checkpointCrosses[checkpointCrossIndex].model->SetPosition(checkpointCrosses[checkpointCrossIndex].model->GetX(), kHiddenY, checkpointCrosses[checkpointCrossIndex].model->GetZ());
                checkpointCrosses[checkpointCrossIndex].timer = kNoTimeRemaining;
            }

            gameState = WaitingToStart;
            stageMsg = "Hit Space to Start";
            winnerText = "";

            playerTime = kNoTimeRemaining;
            npcTime = kNoTimeRemaining;
            health = kMaxHealth;
            damageCooldown = kNoTimeRemaining;

            nextCheckpoint = kStartIndex;
            npcNextCheckpoint = kStartIndex;
            playerLap = kStepOne;
            npcLap = kStepOne;

            boostReady = true;
            isBoosting = false;
            boostOverheated = false;
            boostTimer = kNoTimeRemaining;
            boostCooldownTimer = kNoTimeRemaining;

            cameraMode = ChaseCam;
        }

        if (engine->KeyHit(Key_1))
        {
            cameraMode = ChaseCam;
            ResetChaseCamera(camOffsetX, camOffsetY, camOffsetZ, cameraYaw, cameraPitch);
        }

        if (engine->KeyHit(Key_2))
        {
            cameraMode = FirstPersonCam;
        }

        switch (gameState)
        {
        case WaitingToStart:
        {
            stageMsg = "Hit Space to Start";

            car->SetPosition(car->GetX(), hoverY, car->GetZ());
            npcCar->SetPosition(npcCar->GetX(), npcHoverY, npcCar->GetZ());

            if (engine->KeyHit(Key_Space))
            {
                gameState = Countdown3;
                countdownTimer = kCountdownSecond;
            }
            break;
        }

        case Countdown3:
        {
            stageMsg = kCountdownThreeText;
            countdownTimer -= frameTime;
            car->SetPosition(car->GetX(), hoverY, car->GetZ());
            npcCar->SetPosition(npcCar->GetX(), npcHoverY, npcCar->GetZ());

            if (countdownTimer <= kNoTimeRemaining)
            {
                gameState = Countdown2;
                countdownTimer = kCountdownSecond;
            }
            break;
        }

        case Countdown2:
        {
            stageMsg = kCountdownTwoText;
            countdownTimer -= frameTime;
            car->SetPosition(car->GetX(), hoverY, car->GetZ());
            npcCar->SetPosition(npcCar->GetX(), npcHoverY, npcCar->GetZ());

            if (countdownTimer <= kNoTimeRemaining)
            {
                gameState = Countdown1;
                countdownTimer = kCountdownSecond;
            }
            break;
        }

        case Countdown1:
        {
            stageMsg = kCountdownOneText;
            countdownTimer -= frameTime;
            car->SetPosition(car->GetX(), hoverY, car->GetZ());
            npcCar->SetPosition(npcCar->GetX(), npcHoverY, npcCar->GetZ());

            if (countdownTimer <= kNoTimeRemaining)
            {
                gameState = GoState;
                countdownTimer = kCountdownSecond;
            }
            break;
        }

        case GoState:
        {
            stageMsg = "GO!";
            countdownTimer -= frameTime;
            car->SetPosition(car->GetX(), hoverY, car->GetZ());
            npcCar->SetPosition(npcCar->GetX(), npcHoverY, npcCar->GetZ());

            if (countdownTimer <= kNoTimeRemaining)
            {
                gameState = Racing;
            }
            break;
        }

        case Racing:
        {

            // Create smoke when health is low
            if (health < kSmokeActivationHealth)
            {
                smokeSpawnTimer -= frameTime;

                if (smokeSpawnTimer <= kNoTimeRemaining)
                {
                    smokeSpawnTimer = kSmokeSpawnInterval;

                    for (int smokeIndex = kStartIndex; smokeIndex < (int)smokeModels.size(); smokeIndex++)
                    {
                        if (smokeTimers[smokeIndex] <= kNoTimeRemaining)
                        {
                            float angle = carRotY * kDegreesToRadians;

                            float smokeX = car->GetX() - sin(angle) * kSmokeBackOffset;
                            float smokeZ = car->GetZ() - cos(angle) * kSmokeBackOffset;

                            smokeX += (rand() % (int)kSmokeRandomRange - (int)kSmokeRandomOffset) * kSmokePositionRandomScale;
                            smokeZ += (rand() % (int)kSmokeRandomRange - (int)kSmokeRandomOffset) * kSmokePositionRandomScale;

                            smokeModels[smokeIndex]->SetPosition(
                                smokeX,
                                car->GetY() + kSmokeHeightOffset,
                                smokeZ
                            );

                            smokeTimers[smokeIndex] = kSmokeLifeTime;
                            break;
                        }
                    }
                }
            }

            for (int smokeIndex = kStartIndex; smokeIndex < (int)smokeModels.size(); smokeIndex++)
            {
                if (smokeTimers[smokeIndex] > kNoTimeRemaining)
                {
                    smokeTimers[smokeIndex] -= frameTime;

                    smokeModels[smokeIndex]->MoveY(kSmokeRiseSpeed * frameTime);
                    smokeModels[smokeIndex]->MoveX((rand() % (int)kSmokeRandomRange - (int)kSmokeRandomOffset) * kSmokeDriftScale * frameTime);
                    smokeModels[smokeIndex]->MoveZ((rand() % (int)kSmokeRandomRange - (int)kSmokeRandomOffset) * kSmokeDriftScale * frameTime);

                    if (smokeTimers[smokeIndex] <= kNoTimeRemaining)
                    {
                        smokeTimers[smokeIndex] = kNoTimeRemaining;
                        smokeModels[smokeIndex]->SetPosition(kModelResetX, kHiddenY, kModelResetZ);
                    }
                }
            }

            playerTime += frameTime;
            npcTime += frameTime;

            float leanAngle = kNoTimeRemaining;
            targetPitchAngle = kNoTimeRemaining;

            // Boost stops 
            if (health < kBoostDisabledHealth)
            {
                isBoosting = false;
                boostReady = false;
                boostTimer = kNoTimeRemaining;
            }
            else if (boostOverheated)
            {
                boostCooldownTimer -= frameTime;

                if (boostCooldownTimer <= kNoTimeRemaining)
                {
                    boostCooldownTimer = kNoTimeRemaining;
                    boostOverheated = false;
                    boostReady = true;
                }
            }
            else
            {
                boostReady = true;

                if (engine->KeyHeld(Key_Space))
                {
                    isBoosting = true;
                    boostTimer += frameTime;

                    if (boostTimer > kBoostMaxTime)
                    {
                        isBoosting = false;
                        boostOverheated = true;
                        boostReady = false;
                        boostCooldownTimer = kBoostCooldownTime;
                        boostTimer = kNoTimeRemaining;
                    }
                }
                else
                {
                    isBoosting = false;
                    boostTimer = kNoTimeRemaining;
                }
            }

            Vec2 acceleration = { kNoTimeRemaining, kNoTimeRemaining };
            float angle = carRotY * kDegreesToRadians;
            Vec2 forward = { sin(angle), cos(angle) };

            if (engine->KeyHeld(Key_W))
            {
                float currentThrust = kForwardThrust;

                if (isBoosting)
                {
                    currentThrust *= kBoostMultiplier;
                }

                acceleration = AddVec(acceleration, MulVec(forward, currentThrust));
                targetPitchAngle = kPitchAmount;
            }

            if (engine->KeyHeld(Key_S))
            {
                acceleration = AddVec(acceleration, MulVec(forward, -kReverseThrust));
                targetPitchAngle = -kPitchAmount;
            }

            if (engine->KeyHeld(Key_A))
            {
                carRotY -= kTurnSpeed * frameTime;
                leanAngle = kLeanAmount;
            }

            if (engine->KeyHeld(Key_D))
            {
                carRotY += kTurnSpeed * frameTime;
                leanAngle = -kLeanAmount;
            }

            float currentDrag = kDrag;
            if (boostOverheated)
            {
                currentDrag *= kOverheatDragMultiplier;
            }

            float pitchSmoothSpeed = kPitchSmoothSpeed;
            pitchAngle = pitchAngle + (targetPitchAngle - pitchAngle) * pitchSmoothSpeed * frameTime;

            Vec2 dragForce = MulVec(velocity, -currentDrag);
            velocity = AddVec(velocity, MulVec(AddVec(acceleration, dragForce), frameTime));

            if (LengthVec(velocity) > kMaxSpeed)
            {
                velocity = MulVec(NormaliseVec(velocity), kMaxSpeed);
            }

            float previousCarX = car->GetX();
            float previousCarZ = car->GetZ();

            float newCarX = previousCarX;
            float newCarZ = previousCarZ;

            float testCarX = previousCarX + velocity.x * frameTime;
            
            if (!HitBarrierAtPosition(testCarX, previousCarZ, wallModels, isleModels, hiddenWallModels, wallRotations, isleRotations, hiddenWallRotations))
            {
                newCarX = testCarX;
            }
            else
            {
                velocity.x = -velocity.x * kBarrierBounce;
                DamagePlayer(health, damageCooldown);
                stageMsg = "Hit wall";
            }

            float testCarZ = previousCarZ + velocity.z * frameTime;
            
            if (!HitBarrierAtPosition(newCarX, testCarZ, wallModels, isleModels, hiddenWallModels, wallRotations, isleRotations, hiddenWallRotations))
            {
                newCarZ = testCarZ;
            }
            else
            {
                velocity.z = -velocity.z * kBarrierBounce;
                DamagePlayer(health, damageCooldown);
                stageMsg = "Hit wall";
            }

            for (int tankIndex = kStartIndex; tankIndex < (int)tankModels.size(); tankIndex++)
            {
                if (SphereToSphere(newCarX, newCarZ, kCarRadius, tankModels[tankIndex]->GetX(), tankModels[tankIndex]->GetZ(), kTankRadius))
                {
                    newCarX = previousCarX;
                    newCarZ = previousCarZ;
                    velocity = MulVec(velocity, -kTankBounce);
                    DamagePlayer(health, damageCooldown);
                    stageMsg = "Hit tank";
                    break;
                }
            }

            if (nextCheckpoint < (int)checkpoints.size())
            {
                if (CheckCheckpointPostCollision(newCarX, newCarZ, checkpoints[nextCheckpoint]))
                {
                    newCarX = previousCarX;
                    newCarZ = previousCarZ;
                    velocity = MulVec(velocity, -kCheckpointBounce);
                    DamagePlayer(health, damageCooldown);
                    stageMsg = "Hit checkpoint";
                }
            }

            car->SetPosition(newCarX, hoverY, newCarZ);
            ApplyCarVisuals(car, carRotY, leanAngle, pitchAngle);

            if (nextCheckpoint < (int)checkpoints.size())
            {
                if (PointInCheckpointGap(car->GetX(), car->GetZ(), checkpoints[nextCheckpoint]))
                {
                    ShowCross(checkpointCrosses[nextCheckpoint], checkpoints[nextCheckpoint].x, checkpoints[nextCheckpoint].z);
                    nextCheckpoint++;

                    stageMsg = "Stage " + to_string(nextCheckpoint) + " complete";

                    if (nextCheckpoint >= (int)checkpoints.size())
                    {
                        nextCheckpoint = kStartIndex;
                        playerLap++;

                        if (playerLap > kTotalLaps)
                        {
                            winnerText = "Player Wins! Race Time: " + to_string((int)playerTime) + " s";
                            gameState = RaceComplete;
                        }
                        else
                        {
                            stageMsg = "Lap " + to_string(playerLap) + " started";
                        }
                    }
                }
            }

            npcCar->SetPosition(npcCar->GetX(), npcHoverY, npcCar->GetZ());

            UpdateNPC(npcCar, npcRotY, npcVelocity,
                npcWaypoints, npcWaypoint, frameTime);

            if (npcNextCheckpoint < (int)checkpoints.size())
            {
                if (PointInCheckpointGap(npcCar->GetX(), npcCar->GetZ(), checkpoints[npcNextCheckpoint]))
                {
                    npcNextCheckpoint++;

                    if (npcNextCheckpoint >= (int)checkpoints.size())
                    {
                        npcNextCheckpoint = kStartIndex;
                        npcLap++;

                        if (npcLap > kTotalLaps)
                        {
                            winnerText = "NPC Wins! Race Time: " + to_string((int)npcTime) + " s";
                            gameState = RaceComplete;
                        }
                    }
                }
            }

            if (SphereToSphere(car->GetX(), car->GetZ(), kCarRadius, npcCar->GetX(), npcCar->GetZ(), kCarRadius))
            {
                car->SetPosition(previousCarX, hoverY, previousCarZ);
                velocity = MulVec(velocity, -kNpcBounce);
                DamagePlayer(health, damageCooldown);
                stageMsg = "Hit NPC";
            }

            if (health <= kStartIndex)
            {
                health = kStartIndex;
                stageMsg = "Game Over";
                gameState = GameOver;
            }

            break;
        }

        case RaceComplete:
        {
            car->SetPosition(car->GetX(), hoverY, car->GetZ());
            npcCar->SetPosition(npcCar->GetX(), npcHoverY, npcCar->GetZ());
            velocity.x = kNoTimeRemaining;
            velocity.z = kNoTimeRemaining;
            stageMsg = "Race Complete - Press R to Restart";
            break;
        }

        case GameOver:
        {
            car->SetPosition(car->GetX(), hoverY, car->GetZ());
            npcCar->SetPosition(npcCar->GetX(), npcHoverY, npcCar->GetZ());
            velocity.x = kNoTimeRemaining;
            velocity.z = kNoTimeRemaining;
            stageMsg = "GAME OVER - Press R to restart";
            break;
        }
        }

        int playerProgress = GetProgressScore(playerLap, nextCheckpoint, (int)checkpoints.size());
        int npcProgress = GetProgressScore(npcLap, npcNextCheckpoint, (int)checkpoints.size());

        int racePosition = kRaceCompetitorCount;
        if (playerProgress >= npcProgress) racePosition = kStepOne;

        if (cameraMode == FirstPersonCam)
        {
            UpdateFirstPersonCamera(camera, car, carRotY);
        }
        else
        {
            UpdateChaseCamera(engine, camera, car, carRotY, camOffsetX, camOffsetY, camOffsetZ, cameraYaw, cameraPitch, frameTime);
        }

        DrawUI(font, engine, gameState, stageMsg, playerTime, health, playerLap, kTotalLaps,
            nextCheckpoint + kStepOne, (int)checkpoints.size(), boostReady, isBoosting, boostOverheated,
            boostTimer, boostCooldownTimer, racePosition, winnerText, velocity);
    }

    engine->Delete();
}