// main.cpp文件
#include <Eigen/Dense>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include "Eigen/Core"
#include "Parameters.hpp"
#include "yaml-cpp/yaml.h"

using namespace std;
using namespace Eigen;
using namespace roaddb::trjest::core;

int main() {
    cout << "begin" << endl;
    // load .yaml file
    fstream _file;
    _file.open("../YamlTurorial/default.yaml", ios::in);
    if (!_file) {
        cout << "the file is not in the directory!" << endl;
    } else {
        cout << "the file is here and can be opened" << endl;
    }

    YAML::Node config = YAML::LoadFile(
        "../YamlTurorial/default.yaml");  // there is no need to throw the exception cause yaml will do it automatically
    if (config.IsMap()) {
        cout << "the mode is map" << endl;
    }

    // Get the ImuParams
    if (config["ImuParams"]) {  // seek ImuParams Node
        cout << "Now ImuParams" << endl;
        //        if (config["sigmaBg"]) {  // can not find the subNode
        //            cout << "1.1" << endl;
        //        } else {
        //            cout << "can not find sigmaBg" << endl;
        //        }
    }
    // read data from ImuParams Node
    YAML::Node IMU = config["ImuParams"];
    if (typeid(IMU["ImuParams"]) == typeid(string)) {
        cout << "int" << endl;
    } else {
        cout << "not int" << endl;
    }
    cout << "sigmaBg is " << IMU["sigmaBg"].as<double>() << endl;
    cout << "sigmaBa is " << IMU["sigmaBa"] << endl;
    cout << "sigmaG is " << IMU["sigmaG"] << endl;
    cout << "sigmaA is " << IMU["sigmaA"] << endl;
    cout << "f is " << IMU["f"] << endl;
    // write the data from vector to struct----- Wrong!!!--the it.begin() is sigmaG but not sigmaBg, why!!
    //    std::vector<double> ImuSeq;

    //    for (YAML::const_iterator it = IMU.begin(); it != IMU.end(); ++it) {
    //        cout << "now the it point to " << it->first.as<std::string>() << ": " << it->second.as<double>() << endl;
    //        ImuSeq.push_back(it->second.as<double>());
    //    }
    ImuParameters imu;
    imu.sigmaBg = IMU["sigmaBg"].as<double>();
    imu.sigmaBa = IMU["sigmaBa"].as<double>();
    imu.sigmaG = IMU["sigmaG"].as<double>();
    imu.sigmaA = IMU["sigmaA"].as<double>();
    imu.f = IMU["f"].as<double>();
    // imu.sigmaBg = ImuSeq[0];
    //    imu.sigmaBa = ImuSeq[1];
    //    imu.sigmaG = ImuSeq[2];
    //    imu.sigmaA = ImuSeq[3];
    //    imu.f = ImuSeq[4];
    cout << "the IMU parameters [sigmaBg, sigmaBa, sigmaG, sigmaA, f] = "
         << "[" << imu.sigmaBg << ", " << imu.sigmaBa << ", " << imu.sigmaG << ", " << imu.sigmaA << ", " << imu.f
         << "]" << endl;

    // Get the GpsParams
    if (config["GpsParams"]) {
        cout << "Now GpsParams" << endl;
    }
    // read data from ImuParams Node
    YAML::Node GPS = config["GpsParams"];
    cout << "sigmaP is " << GPS["sigmaP"] << endl;
    cout << "sigmaV is " << GPS["sigmaV"] << endl;
    cout << "sigmaC is " << GPS["sigmaC"] << endl;
    cout << "f is " << GPS["f"] << endl;
    // write the data from vector to struct
    GpsParameters gpsParams;
    // from gpsSigmaP
    YAML::Node gpsSigmaP = GPS["sigmaP"];
    vector<double> Gps_sigmaP_Seq;
    for (std::size_t i = 0; i < gpsSigmaP.size(); i++) {
        std::cout << gpsSigmaP[i].as<double>() << "\n";
        Gps_sigmaP_Seq.push_back(gpsSigmaP[i].as<double>());
    }
    gpsParams.sigmaP << Gps_sigmaP_Seq[0], Gps_sigmaP_Seq[1], Gps_sigmaP_Seq[2];
    // from gpsSigmaV
    YAML::Node gpsSigmaV = GPS["sigmaV"];
    vector<double> Gps_sigmaV_Seq;
    for (std::size_t i = 0; i < gpsSigmaV.size(); i++) {
        std::cout << gpsSigmaV[i].as<double>() << "\n";
        Gps_sigmaV_Seq.push_back(gpsSigmaV[i].as<double>());
    }
    gpsParams.sigmaV << Gps_sigmaV_Seq[0], Gps_sigmaV_Seq[1], Gps_sigmaV_Seq[2];
    // from gpsSigmaC
    gpsParams.sigmaC = GPS["sigmaC"].as<double>();
    // from gpsf
    gpsParams.f = GPS["f"].as<double>();
    cout << "the GPS parameters [sigmap, sigmav, sigmaC, f] = "
         << "[" << gpsParams.sigmaP << ", " << gpsParams.sigmaV << ", " << gpsParams.sigmaC << ", " << gpsParams.f
         << "]" << endl;

    // Get the Camera Params
    if (config["CameraParams"]) {
        cout << "Now CameraParams" << endl;
    }
    // read data from CameraParams Node
    YAML::Node Cam = config["CameraParams"];
    cout << "f is " << Cam["f"] << endl;
    cout << "c is " << Cam["c"] << endl;
    cout << "k is " << Cam["k"] << endl;
    cout << "p is " << Cam["p"] << endl;
    cout << "Tcb is " << Cam["Tcb"] << endl;
    // write the data from vector to struct
    CameraParameters cameraParams;
    // from f
    YAML::Node Cam_f = Cam["f"];
    vector<double> Cam_f_Seq;
    for (std::size_t i = 0; i < Cam_f.size(); i++) {
        std::cout << Cam_f[i].as<double>() << "\n";
        Cam_f_Seq.push_back(Cam_f[i].as<double>());
    }
    cameraParams.f << Cam_f_Seq[0], Cam_f_Seq[1];
    // from c
    YAML::Node Cam_c = Cam["c"];
    vector<double> Cam_c_Seq;
    for (std::size_t i = 0; i < Cam_c.size(); i++) {
        std::cout << Cam_c[i].as<double>() << "\n";
        Cam_c_Seq.push_back(Cam_c[i].as<double>());
    }
    cameraParams.c << Cam_c_Seq[0], Cam_c_Seq[1];
    // from k
    YAML::Node Cam_k = Cam["k"];
    vector<double> Cam_k_Seq;
    for (std::size_t i = 0; i < Cam_k.size(); i++) {
        std::cout << Cam_k[i].as<double>() << "\n";
        Cam_k_Seq.push_back(Cam_k[i].as<double>());
    }
    cameraParams.k << Cam_k_Seq[0], Cam_k_Seq[1];
    // from p
    YAML::Node Cam_p = Cam["p"];
    vector<double> Cam_p_Seq;
    for (std::size_t i = 0; i < Cam_p.size(); i++) {
        std::cout << Cam_p[i].as<double>() << "\n";
        Cam_p_Seq.push_back(Cam_p[i].as<double>());
    }
    cameraParams.p << Cam_p_Seq[0], Cam_p_Seq[1];
    // from Tcb
    YAML::Node Cam_Tcb = Cam["Tcb"];
    vector<double> Cam_Tcb_Seq;
    for (std::size_t i = 0; i < Cam_Tcb.size(); i++) {
        std::cout << Cam_Tcb[i].as<double>() << "\n";
        Cam_Tcb_Seq.push_back(Cam_Tcb[i].as<double>());
    }
    cameraParams.Tcb << Cam_Tcb_Seq[0], Cam_Tcb_Seq[1], Cam_Tcb_Seq[2], Cam_Tcb_Seq[3], Cam_Tcb_Seq[4], Cam_Tcb_Seq[5],
        Cam_Tcb_Seq[6], Cam_Tcb_Seq[7], Cam_Tcb_Seq[8], Cam_Tcb_Seq[9], Cam_Tcb_Seq[10], Cam_Tcb_Seq[11],
        Cam_Tcb_Seq[12], Cam_Tcb_Seq[13], Cam_Tcb_Seq[14], Cam_Tcb_Seq[15];
    cout << "the Camera parameters [f, c, k, p, Tcb] = "
         << "[" << cameraParams.f << ", " << cameraParams.c << ", " << cameraParams.k << ", " << cameraParams.p
         << cameraParams.Tcb << "]" << endl;

    // Get the PreProcess Config
    if (config["PreprocessConfig"]) {
        cout << "Preprocess Configuration" << endl;
    }
    // read data from PreProcess Config Node
    YAML::Node PreproConfig = config["PreprocessConfig"];
    cout << "EnableRepeatedDataCheck is " << PreproConfig["EnableRepeatedDataCheck"] << endl;
    cout << "EnableTimeRegionCheck is " << PreproConfig["EnableTimeRegionCheck"] << endl;
    cout << "EnableEnoughLostDataCheck is " << PreproConfig["EnableEnoughLostDataCheck"] << endl;
    cout << "EnableAccumulatedGpsDataProcess is " << PreproConfig["EnableAccumulatedGpsDataProcess"] << endl;
    // write the data from vector to struct----- Wrong!!!--the it.begin() is sigmaG but not sigmaBg, why!!
    //    std::vector<bool> PreProConfigSeq;

    //    for (YAML::const_iterator it = PreproConfig.begin(); it != PreproConfig.end(); ++it) {
    //        cout << "now the it point to " << it->first.as<std::string>() << ": " << it->second.as<bool>() << endl;
    //        PreProConfigSeq.push_back(it->second.as<bool>());
    //    }
    PreprocessConfig preproCon;

    preproCon.enableRepeatedDataCheck = PreproConfig["EnableRepeatedDataCheck"].as<bool>();
    preproCon.enableTimeRegionCheck = PreproConfig["EnableTimeRegionCheck"].as<bool>();
    preproCon.enableEnoughLostDataCheck = PreproConfig["EnableEnoughLostDataCheck"].as<bool>();
    preproCon.enableAccumulatedGpsDataProcess = PreproConfig["EnableAccumulatedGpsDataProcess"].as<bool>();
    cout << "the Preprocess Config [EnableRepeatedDataCheck, EnableTimeRegionCheck, EnableEnoughLostDataCheck, "
            "EnableAccumulatedGpsDataProcess] = "
         << "[" << preproCon.enableRepeatedDataCheck << ", " << preproCon.enableTimeRegionCheck << ", "
         << preproCon.enableEnoughLostDataCheck << ", " << preproCon.enableAccumulatedGpsDataProcess << "]" << endl;

    // Get the EKF Config
    if (config["EkfConfig"]) {
        cout << "5" << endl;
    }
    // read data from EKF Config Node
    YAML::Node EKFConfig = config["EkfConfig"];
    YAML::Node IniState = EKFConfig["InitState"];
    cout << "rot is " << IniState["rot"] << endl;
    cout << "pos is " << IniState["pos"] << endl;
    cout << "vel is " << IniState["vel"] << endl;
    cout << "gyroBias is " << IniState["gyroBias"] << endl;
    cout << "accBbias is " << IniState["accBias"] << endl;
    cout << "InitVar is " << EKFConfig["InitVar"] << endl;
    cout << "EnableSmooth is " << EKFConfig["EnableSmooth"] << endl;
    cout << "EnableStationCheck is " << EKFConfig["EnableStationCheck"] << endl;

    cout << "hello world" << endl;

    return 0;
    /* //the basic emitter-example1
            YAML::Emitter out;
            out << "Hello, World!";
            out << YAML::BeginSeq;
            out << "egg";
            out << "bread";
            out << "milk";
            out << YAML::EndSeq;
    */

    /* //the basic emitter-example2
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "name";
    out << YAML::Value << "Ryan Braun";
    out << YAML::Key << "age";
    out << YAML::Value << "25";
    out << YAML::Key << "children";
    out << YAML::Value << YAML::BeginSeq << "Sasha"
        << "Malia" << YAML::EndSeq;
    out << YAML::EndMap;
    */

    /* //the basic emitter-example3
        std::vector<int> squares;
        squares.push_back(1);
        squares.push_back(4);
        squares.push_back(9);
        squares.push_back(16);

        std::map<std::string, int> ages;
        ages["Daniel"] = 26;
        ages["Jesse"] = 24;

        out << YAML::BeginSeq;
        out << YAML::Flow << squares;
        out << ages;
        out << YAML::EndSeq;
        std::cout << "Here's the output YAML:\n" << out.c_str() << endl;  // prints "Hello, World!"
        */

    /*// You can check what kind it is:
    YAML::Node node = YAML::Load("[1, 2, 3]");
    assert(node.Type() == YAML::NodeType::Sequence);  // How to know the result
    assert(node.IsSequence());                        // a shortcut!
    // cout << "i = " << i << endl;
    // cout << "j = " << j << endl;
    */

    /*// Collection nodes (sequences and maps) act somewhat like STL vectors and maps:  --example1
    YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
    for (std::size_t i = 0; i < primes.size(); i++) {
        std::cout << primes[i].as<int>() << "\n";
    }
    // or:
    for (YAML::const_iterator it = primes.begin(); it != primes.end(); ++it) {
        std::cout << it->as<int>() << "\n";
    }

    primes.push_back(13);
    assert(primes.size() == 6);
    */

    /* // Collection nodes (sequences and maps) act somewhat like STL vectors and maps:  --example2
    YAML::Node lineup = YAML::Load("{1B: Prince Fielder, 2B: Rickie Weeks, LF: Ryan Braun}");
    for (YAML::const_iterator it = lineup.begin(); it != lineup.end(); ++it) {
        std::cout << "Playing at " << it->first.as<std::string>() << " is " << it->second.as<std::string>() <<
    "\n";
    }

    lineup["RF"] = "Corey Hart";
    lineup["C"] = "Jonathan Lucroy";
    assert(lineup.size() == 5);
    */
}
