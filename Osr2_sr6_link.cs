using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BepInEx;
using BepInEx.Configuration;
using HarmonyLib;
using UnityEngine;
using KKAPI.Utilities;
using Studio;
using System.IO;
using System.Net;
using System.Net.Sockets;



namespace KK_osr2_sr6_link
{



    [BepInPlugin("org.bepinex.plugins.osr2_sr6_link", "Osr2_sr6_link", "1.0.0")]
    [BepInProcess("CharaStudio")]
    public class Osr2_sr6_link : BaseUnityPlugin 
    {


        public string female = "chaF_001";
        public GameObject femalehead;
        public GameObject femaleRoot;
        public GameObject vagina;
        public GameObject femalethightL;
        public GameObject femalethightR;
        public GameObject femalehips;


        public string male = "chaM_001";

        public GameObject malehead;
        public GameObject maleRoot;
        public GameObject penis;
        public GameObject malethightL;
        public GameObject malethightR;
        public GameObject malehips;

        public float last_pitch = 2;
        public float last_roll = 2;



        public static bool cycle = false;
        public static string scene_path = "no";
        private static bool resampled = true;
        public bool start_sampled = false;
        public string currentDirectory = Directory.GetCurrentDirectory().Replace("\\","/");

        List<float> inserts = new List<float>();
        List<float> surges = new List<float>();
        List<float> sways = new List<float>();
        List<float> twists = new List<float>();
        List<float> pitchs = new List<float>();
        List<float> rolls = new List<float>();
        List<double> play_times = new List<double>();
        double last_playtime = 0;
        double last_interval_time = 0;


        int roundedPlaybackTime = 1;
        int roundedIntervalTime = 1;
        int last_roundedPlaybackTime = 1;




        //window
        public Rect windowRect = new Rect(50, 50, 500, 300);
        public ConfigEntry<int> L0;
        public ConfigEntry<int> L1;
        public ConfigEntry<int> L2;
        public ConfigEntry<int> R0;
        public ConfigEntry<int> R1;
        public ConfigEntry<int> R2;
        public ConfigEntry<int> A1;
        public ConfigEntry<double> interval_time;




        //tcpclientSocket 
        private Socket clientSocket;
        private bool link = false;
        private DateTime start_time = DateTime.Now;
        private DateTime currentTime = DateTime.Now;
        public ConfigEntry<int> link_interval;
        private int link_interval_time;
        public ConfigEntry<string> server_ip;
        private IPAddress serverIP;
        public ConfigEntry<int> server_port;
        private int port;


        private void Link_server() {
            if (!link) {
                currentTime = DateTime.Now;
                int elapsedMilliseconds = (int)(currentTime - start_time).TotalMilliseconds;
                link_interval_time = link_interval.Value;
                if (elapsedMilliseconds > link_interval_time)
                {
                    start_time = DateTime.Now;
                    try
                    {
                        clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                        serverIP = IPAddress.Parse(server_ip.Value);
                        port = server_port.Value;
                        clientSocket.Connect(serverIP, port);
                        link = true;
                        Logger.LogInfo($"link server {serverIP.ToString()}:{port} true");
                    }
                    catch
                    {
                        link = false;
                        Logger.LogInfo($"link server {serverIP.ToString()}:{port} false");
                        clientSocket.Close();
                    }
                }
            }           
        }



        //计算具体部位
        void Start()
        {
            Harmony.CreateAndPatchAll(typeof(Osr2_sr6_link));
            Logger.LogInfo("KK osr2 sr6 link start");
            server_ip = Config.Bind("link setting", "Server IP", "127.0.0.1", "input app server ip");
            server_port = Config.Bind("link setting", "Server port", 8000, "input app server port id");
            link_interval = Config.Bind("link setting", "relink interval", 5000, "setting relink time(Millisecond)");
            interval_time = Config.Bind<double>("sampled setting", "interval_time", 0.1, "Calculate interval in timeline");
            Config.Bind("link setting", "Link State", "", new ConfigDescription("Desc", null, new ConfigurationManagerAttributes { CustomDrawer = MyDrawer1 }));
            Config.Bind("sampled setting", "Sample", "", new ConfigDescription("abc", null, new ConfigurationManagerAttributes { CustomDrawer = MyDrawer2 }));
        }

        public void MyDrawer1(BepInEx.Configuration.ConfigEntryBase entry)
        {
            GUILayout.BeginHorizontal();
            if (!link)
            {
                GUILayout.Label("Waiting server to link");
                if (GUILayout.Button("connect"))
                {
                    try
                    {
                        clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                        serverIP = IPAddress.Parse(server_ip.Value);
                        port = server_port.Value;
                        clientSocket.Connect(serverIP, port);
                        link = true;
                        Logger.LogInfo($"link server {serverIP.ToString()}:{port} true");
                    }
                    catch
                    {
                        link = false;
                        Logger.LogInfo($"link server {serverIP.ToString()}:{port} false");
                        clientSocket.Close();
                    }
                }
            }
            else 
            {
                GUILayout.Label("link server succeed");
                if (GUILayout.Button("disconnect"))
                {
                    clientSocket.Close();
                    link = false;
                }
            }
            GUILayout.EndHorizontal();
        }


        public void MyDrawer2(BepInEx.Configuration.ConfigEntryBase entry)
        {
            GUILayout.BeginVertical();
            if (cycle)
            {
                if (GUILayout.Button("start resampled "))
                {
                    start_sampled = true;
                }
            }
            else {
                if (GUILayout.Button("start sampled "))
                {
                    start_sampled = true;
                }
            }
            GUILayout.EndVertical();
        }


        [HarmonyPostfix]
        [HarmonyPatch(typeof(SceneLoadScene), "LoadScene")]
        public static void Getscene_path(SceneLoadScene __instance, string _path)
        {
            Debug.Log("New_sex_Start!\n");
            Debug.Log($"path:{_path}");
            cycle = false;
            scene_path = _path;
            resampled = true;
        }




        public void TraverseChildren(Transform parent, string path = "")
        {
            foreach (Transform child in parent)
            {
                string childPath = path + "/" + child.name;
                Logger.LogInfo(childPath);

                TraverseChildren(child, childPath);
            }
        }
        public String FindRootObjectpath(String path)
        {
            Transform currentTransform = GameObject.Find(path).transform;
            path = currentTransform.name;
            while (currentTransform.parent != null)
            {
                currentTransform = currentTransform.parent;
                path = currentTransform.name + "/" + path;
            }

            return path;
        }



        public float Angle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4)
        {

            Vector3 line1 = p2 - p1;
            Vector3 line2 = p3 - p4;
            float dotProduct = Vector3.Dot(line1.normalized, line2.normalized);
            float angle = (float)(Math.Acos(dotProduct) * (180 / Math.PI));
            if (angle < 0) { angle = -angle; }
            if (angle >= 90 && angle < 180) { angle = 180 - angle; }
            else if (angle >= 180 && angle < 270) { angle -= 180; }
            else if (angle >= 270 && angle < 360) { angle = 180 - (angle - 180); }
            return angle;
        }


        public float Pitch_angle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) //vagina,femalehips,penis,maleL,maleR.
        {
            Vector3 v1 = p1 - p3;
            Vector3 v2 = p1 - p4;
            Vector3 normal = Vector3.Cross(v1, v2).normalized;
            Vector3 lineDir = (p2 - p1).normalized;
            // 

            // 
            Vector3 a = femalehead.transform.position - femalehips.transform.position;
            Vector3 b = malehead.transform.position - malehips.transform.position;
            // 
            float angle = Vector3.Angle(lineDir, normal);

            float dotProduct = Vector3.Dot(a, b);
            if ((-0.00001 < dotProduct && dotProduct <= 0) || (0 < dotProduct && dotProduct <= 0.00001)) { dotProduct = last_pitch; }
            last_pitch = dotProduct;

            if (angle > 90) { angle = 180 - angle; }
            if (dotProduct < 0) { angle = 180 -angle; }
            if (angle > 90) { angle -= 90; }
            else { angle = -(90 - angle); }
            return angle;
        }

        public float Roll_angle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) //vagina,femalehips,maleL,maleR,malehips.
        {
            // 1.  a  normal_a
            Vector3 v1 = p1 - p3;
            Vector3 v2 = p1 - p4;
            Vector3 normal_a = Vector3.Cross(v1, v2).normalized;

            // 2.  b  normal_b
            Vector3 midPoint = (p3 + p4) / 2;
            Vector3 p1MidPoint = midPoint - p1;
            Vector3 normal_b = p1MidPoint.normalized;

            // 3. p2  b  _p2
            float distance = Vector3.Dot(p2 - p1, normal_b);
            Vector3 _p2 = p2 - distance * normal_b;
            float angle = Vector3.Angle(_p2 - p1, normal_a);
            Vector3 normal = Vector3.Cross(normal_a, p1MidPoint);//p3->p4
            float dotProduct = Vector3.Dot(_p2 - p1, normal);
            if ((-0.00001 < dotProduct && dotProduct <= 0) || (0 < dotProduct && dotProduct <= 0.00001)) { dotProduct = last_roll; }
            last_roll = dotProduct;
            // 
            if (angle > 90) { angle = 180 - angle; }
            if (dotProduct < 0) { angle = -angle; }
            //if (angle > 60) { angle = 60; }
            //else if (angle < -60) { angle = -60; }
            return angle;
        }

        public float Twist_angle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 p5) //femaleL,femaleR,penis,maleL,maleR.
        {
            // 1.  a  normal_a
            Vector3 v1 = p3 - p4;
            Vector3 v2 = p3 - p5;
            Vector3 normal_a = Vector3.Cross(v1, v2).normalized;
            // 2.  p1 a  _p1
            float distance1 = Vector3.Dot(p1 - p3, normal_a);
            Vector3 _p1 = p1 - distance1 * normal_a;

            // 3.  p2 a  _p2
            float distance2 = Vector3.Dot(p2 - p3, normal_a);
            Vector3 _p2 = p2 - distance2 * normal_a;

            Vector3 midPoint = (p4 + p5) / 2;
            Vector3 p3MidPoint = midPoint - p3;
            Vector3 normal = Vector3.Cross(normal_a, p3MidPoint).normalized;

            Vector3 _p1_p2 = _p1 - _p2;
            float angle = Vector3.Angle(_p1_p2, normal);
            float dotProduct = Vector3.Dot(p1-p2, p4-p5);
            if ((-0.00001 < dotProduct && dotProduct <= 0) || (0 < dotProduct && dotProduct <= 0.00001)) { dotProduct = last_roll; }
            last_roll = dotProduct;
            if (angle > 90) { angle = 180 - angle; }
            if (dotProduct > 0) { angle = -angle; }
            return angle;
        }

        public float[] Get_position(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) //vagina,penis,maleL,maleR.
        {

            Vector3 v1 = p3 - p1;
            Vector3 v2 = p4 - p1;
            Vector3 normal = Vector3.Cross(v1, v2).normalized;

            float distance = Vector3.Dot(p1 - p2, normal);
            Vector3 _p2 = p2 - normal * distance;

            Vector3 midPoint = (p3 + p4) / 2;


            Vector3 p1MidPoint = (midPoint - p1);

            
            Vector3 p1_p2 = _p2 - p1;
            
            float sway = Vector3.Cross(p1_p2, p1MidPoint).magnitude / p1MidPoint.magnitude;
            Vector3 n = p1MidPoint.normalized;
            float d = -Vector3.Dot(n, p1);
            float x = _p2.x;
            float y = _p2.y;
            float z = _p2.z;
            float surge = Math.Abs(n.x * x + n.y * y + n.z * z + d) / Mathf.Sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

            float[] position = { surge,sway }; 
            return position;
        }

        private void Setting_range() {           
            if (interval_time.Value > 1 || interval_time.Value < 0.1) { interval_time.Value = 0.1; }
            if (last_interval_time != interval_time.Value) { resampled = true; last_interval_time = interval_time.Value; }
            if (server_port.Value < 0 || server_port.Value > 9999) { server_port.Value = 8000; }
        }


        public void Update()
        {
            Setting_range();
            Link_server();
            if (link) {
                if (scene_path != "no")
                {
                    string target_path = scene_path.Replace("/UserData/studio/scene/", "").Replace(".png", "").Replace(currentDirectory, "").Replace("/CharaStudio_Data/..", "");
                    string filePath = (currentDirectory + "/UserData/KK_osr_sr6_link/" + target_path + ".txt").Replace("/UserData//studio/scene/", "");
                    if (start_sampled) { try { File.Delete(filePath); } catch { } }
                 
                    if (!File.Exists(filePath))
                    {
                        femaleRoot = GameObject.Find(female);
                        maleRoot = GameObject.Find(male);
                        if (femaleRoot != null && maleRoot != null)
                        {
                            if (!start_sampled) { return; }
                            if (Timeline.Timeline.isPlaying)
                            {
                                Timeline.Timeline.Pause();
                            }
                            if (resampled)
                            {
                                Timeline.Timeline.Seek(0);
                                resampled = false;
                                last_playtime = 0;
                            }
                            Logger.LogInfo("playbackTime:" + Timeline.Timeline.playbackTime);
                            if (Math.Round(last_playtime, 3) != Math.Round(Timeline.Timeline.playbackTime, 3))
                            {
                                Logger.LogInfo("Due to playtime have changed dramatically,restart compute!Please not change playtime when first compute.");
                                resampled = true;
                                return;
                            }
                            if ((float)Math.Round(Timeline.Timeline.playbackTime + interval_time.Value, 3) < Timeline.Timeline.duration)
                            {
                                Timeline.Timeline.Seek((float)Math.Round(Timeline.Timeline.playbackTime + interval_time.Value, 3));
                                last_playtime = Math.Round(last_playtime, 3) + Math.Round(interval_time.Value, 3);
                            }
                            else { Timeline.Timeline.Seek(Timeline.Timeline.duration); }

                            femalehead = GameObject.Find(female + "BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips/cf_j_spine01/cf_j_spine02/cf_j_spine03/cf_j_neck/cf_j_head");

                            femalethightL = GameObject.Find(female + "/BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips/cf_j_waist01/cf_j_waist02/cf_j_thigh00_L");

                            femalethightR = GameObject.Find(female + "/BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips/cf_j_waist01/cf_j_waist02/cf_j_thigh00_R");

                            femalehips = GameObject.Find(female + "/BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips");

                            vagina = GameObject.Find(female + "/BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips/cf_j_waist01/cf_j_waist02/cf_d_kokan/cf_j_kokan/a_n_kokan");

                            penis = GameObject.Find(male + "/BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips/cf_j_waist01/cf_j_waist02/cf_d_kokan/cm_J_dan_top/cm_J_dan100_00/cm_J_dan101_00/a_n_dan");

                            malehips = GameObject.Find(male + "/BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips");

                            malethightL = GameObject.Find(male + "/BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips/cf_j_waist01/cf_j_waist02/cf_j_thigh00_L");
                            //Logger.LogInfo("BepIn : cf_j_thigh00_L:" + femalethightL.name);//cf_j_waist02
                            malethightR = GameObject.Find(male + "/BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips/cf_j_waist01/cf_j_waist02/cf_j_thigh00_R");


                            malehead = GameObject.Find(male + "BodyTop/p_cf_body_bone/cf_j_root/cf_n_height/cf_j_hips/cf_j_spine01/cf_j_spine02/cf_j_spine03/cf_j_neck/cf_j_head");
                            //Vector3[] femalethight = P_(vagina.transform.position, femalethightL.transform.position, femalethightR.transform.position, femalehips.transform.position);

                            Vector3 offset = penis.transform.position - vagina.transform.position;

                            Vector3 _vagina = vagina.transform.position + offset;
                            Vector3 _femalehps = femalehips.transform.position + offset;
                            Vector3 __vagina = (femalethightL.transform.position + femalethightR.transform.position) / 2 + offset;


                            float dis = Vector3.Distance(penis.transform.position, vagina.transform.position);
                            float pitch_angle = Pitch_angle(_vagina, _femalehps, malethightL.transform.position, malethightR.transform.position);
                            float roll_angle = Roll_angle(__vagina, _femalehps, malethightL.transform.position, malethightR.transform.position);
                            float twist_angle = Twist_angle(femalethightL.transform.position, femalethightR.transform.position, penis.transform.position, malethightL.transform.position, malethightR.transform.position);
                            float[] postiton = Get_position(vagina.transform.position, penis.transform.position, malethightL.transform.position, malethightR.transform.position);
                            float surge = postiton[0];
                            float sway = postiton[1];
                            if (pitch_angle < 0) { surge = -surge; }
                            if (roll_angle < 0) { sway = -sway; }
                            if (!cycle)
                            {
                                inserts.Add(dis);
                                surges.Add(surge);
                                sways.Add(sway);
                                twists.Add(twist_angle);
                                pitchs.Add(pitch_angle);
                                rolls.Add(roll_angle);
                                play_times.Add(Math.Round(last_playtime, 3));
                            }
                            Logger.LogInfo("dis:" + dis + "" + "pitch_angle:" + pitch_angle + "°" + "roll_angle:" + roll_angle + "°" + "twist_angle:" + twist_angle + "°");
                            Logger.LogInfo("surge:" + offset.x + "" + "sway:" + offset.y);
                            Logger.LogInfo("\n");


                            float bodywidth = Vector3.Distance(femalethightL.transform.position, femalethightR.transform.position) * 3;
                            if (Timeline.Timeline.playbackTime == Timeline.Timeline.duration) { cycle = true; }
                            if (cycle)
                            {
                                start_sampled = false;
                                Logger.LogInfo("finish!!!!!!!!!\n\n\n\n");

                                string fileDir = Path.GetDirectoryName(filePath);
                                if (!File.Exists(filePath))
                                {
                                    Logger.LogInfo("creatting script:" + filePath);
                                    if (!Directory.Exists(fileDir))
                                    {
                                        // 
                                        Directory.CreateDirectory(fileDir);
                                    }
                                    using (StreamWriter writer = File.CreateText(filePath))
                                    {                                    // 
                                        for (int i = 0; i < inserts.Count(); i++)
                                        {
                                            writer.WriteLine(
                                                inserts[i] + "/"
                                                + surges[i] + "/"
                                                + sways[i] + "/"
                                                + twists[i] + "/"
                                                + pitchs[i] + "/"
                                                + rolls[i] + "/"
                                                + play_times[i] + "/"
                                                + Timeline.Timeline.duration + "/"
                                                + bodywidth
                                                );
                                        }
                                    }
                                }
                                inserts.Clear();
                                surges.Clear();
                                sways.Clear();
                                twists.Clear();
                                pitchs.Clear();
                                rolls.Clear();
                                play_times.Clear();
                            }

                        }

                    }
                    else
                    {
                        if (link && Timeline.Timeline.isPlaying)
                        {
                            int index = 0;                           
                            roundedPlaybackTime = (int)(Math.Round(Timeline.Timeline.playbackTime, 1)*10);
                            roundedIntervalTime = (int)(Math.Round(interval_time.Value, 1)*10);
                            if (roundedPlaybackTime == last_roundedPlaybackTime) { return; }
                            last_roundedPlaybackTime = roundedPlaybackTime;
                            if (roundedPlaybackTime == 0 || roundedPlaybackTime >= roundedIntervalTime) {
                                if (roundedPlaybackTime == 0) { index = 0; }
                                else if (roundedPlaybackTime >= roundedIntervalTime) {
                                    if (roundedPlaybackTime % roundedIntervalTime == 0) { index = roundedPlaybackTime / roundedIntervalTime; }
                                }
                            }
                            Logger.LogInfo("index:" + index);
                            string message = $"{filePath}|{index}|{interval_time.Value}";
                            byte[] data = Encoding.UTF8.GetBytes(message);
                            try
                            {
                                clientSocket.Send(data);
                            }
                            catch
                            {
                                Logger.LogInfo("Server close.");
                                clientSocket.Close();
                                link = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

