using ActionGame;
using BepInEx;
using BepInEx.Configuration;
using BepInEx.Logging;
using HarmonyLib;
using HarmonyLib.Tools;
using KKAPI.Utilities;
using NodeCanvas.Tasks.Actions;
using Studio;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using UnityEngine;
using static KK_osr2_sr6_link.Osr2_sr6_link;




namespace KK_osr2_sr6_link
{


    [BepInPlugin("org.bepinex.plugins.osr2_sr6_link", "Osr2_sr6_link", "3.0.0")]
    [BepInProcess("CharaStudio")]
    public class Osr2_sr6_link : BaseUnityPlugin
    {
        public static int scanning_mode = 0;

        // chara
        Dictionary<GameObject, String> charas = new Dictionary<GameObject,String>();     
        Dictionary<GameObject, String> female_charas =  new  Dictionary <GameObject, String>();
        Dictionary<GameObject, String> male_charas = new Dictionary <GameObject, String> ();
        public ConfigEntry<int> charas_num;

        public string female = "chaF_001";
        public GameObject femalehead;
        public GameObject femaleRoot;
        public GameObject vagina;
        public GameObject femalethightL;
        public GameObject femalethightR;
        public GameObject femalehips;
        public GameObject femaleearL;
        public GameObject femaleearR;
        public GameObject femalemouth;
        public GameObject femalebreastL;
        public GameObject femalebreastR;
        public GameObject femalehand0L;
        public GameObject femalehand1L;
        public GameObject femalehand2L;
        public GameObject femalehand0R;
        public GameObject femalehand1R;
        public GameObject femalehand2R;

        public string male = "chaM_001";

        public GameObject malehead;
        public GameObject maleRoot;
        public GameObject penis;
        public GameObject malethightL;
        public GameObject malethightR;
        public GameObject malehips;


        public float last_pitch = 2;
        public float last_roll = 2;
        public float last_twist = 2;



        public static bool cycle = false;
        public static string scene_path = "no";
        private static bool resampled = true;
        public bool start_sampled = false;
        public static string currentDirectory = Directory.GetCurrentDirectory().Replace("\\", "/");

        private List<float> inserts = new List<float>();
        private List<float> surges = new List<float>();
        private List<float> sways = new List<float>();
        private List<float> twists = new List<float>();
        private List<float> pitchs = new List<float>();
        private List<float> rolls = new List<float>();
        private List<double> play_times = new List<double>();


        private List<float> blowjob_inserts = new List<float>();
        private List<float> blowjob_surges = new List<float>();
        private List<float> blowjob_sways = new List<float>();
        private List<float> blowjob_twists = new List<float>();
        private List<float> blowjob_pitchs = new List<float>();
        private List<float> blowjob_rolls = new List<float>();

        private List<float> breastsex_inserts = new List<float>();
        private List<float> breastsex_surges = new List<float>();
        private List<float> breastsex_sways = new List<float>();
        private List<float> breastsex_twists = new List<float>();
        private List<float> breastsex_pitchs = new List<float>();
        private List<float> breastsex_rolls = new List<float>();

        private List<float> handjobL_inserts = new List<float>();
        private List<float> handjobL_surges = new List<float>();
        private List<float> handjobL_sways = new List<float>();
        private List<float> handjobL_twists = new List<float>();
        private List<float> handjobL_pitchs = new List<float>();
        private List<float> handjobL_rolls = new List<float>();

        private List<float> handjobR_inserts = new List<float>();
        private List<float> handjobR_surges = new List<float>();
        private List<float> handjobR_sways = new List<float>();
        private List<float> handjobR_twists = new List<float>();
        private List<float> handjobR_pitchs = new List<float>();
        private List<float> handjobR_rolls = new List<float>();


        public struct Action_data
        {
            public List<float> inserts;
            public List<float> surges;
            public List<float> sways;
            public List<float> twists;
            public List<float> pitchs;
            public List<float> rolls;

            public List<float> blowjob_inserts;
            public List<float> blowjob_surges;
            public List<float> blowjob_sways;
            public List<float> blowjob_twists;
            public List<float> blowjob_pitchs;
            public List<float> blowjob_rolls;

            public List<float> breastsex_inserts;
            public List<float> breastsex_surges;
            public List<float> breastsex_sways;
            public List<float> breastsex_twists;
            public List<float> breastsex_pitchs;
            public List<float> breastsex_rolls;

            public List<float> handjobL_inserts;
            public List<float> handjobL_surges;
            public List<float> handjobL_sways;
            public List<float> handjobL_twists;
            public List<float> handjobL_pitchs;
            public List<float> handjobL_rolls;

            public List<float> handjobR_inserts;
            public List<float> handjobR_surges;
            public List<float> handjobR_sways;
            public List<float> handjobR_twists;
            public List<float> handjobR_pitchs;
            public List<float> handjobR_rolls;

            public List<float> bodywidths;
            public string charas_name;



        }
        private List<Action_data> action_list = new List<Action_data>();

        private double last_playtime = 0;
        private double last_interval_time = 0;


        private int roundedPlaybackTime = 1;
        private int roundedIntervalTime = 1;
        private int last_roundedPlaybackTime = 1;




        //window
        public double interval_time = 0.1;
        public ConfigEntry<bool> autorelink;




        //tcpclientSocket 
        private static Socket clientSocket;
        private byte[] buffer = new byte[1024];
        private Thread clientlistener;
        private bool end = false;
        private static bool link = false;
        private DateTime start_time = DateTime.Now;
        private DateTime currentTime = DateTime.Now;
        public ConfigEntry<int> link_interval;
        private int link_interval_time;
        public ConfigEntry<string> server_ip;
        private IPAddress serverIP;
        public ConfigEntry<int> server_port;
        private int port;

       
        private void Link_server()
        {
            if (!link)
            {
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
                        Logger.LogInfo($"link server {serverIP.ToString()}:{port} false,try to relink in {link_interval_time.ToString()}ms");
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
            autorelink = Config.Bind("link setting", "autorelink", true, "setting relink time(Millisecond)");           
            Config.Bind("link setting", "Link State", "", new ConfigDescription("Click to connect app", null, new ConfigurationManagerAttributes { CustomDrawer = MyDrawer1 }));
            charas_num = Config.Bind("sampled setting", "charas_num", 10, "Scanning of number of charas of the same sex");
            Config.Bind("sampled setting", "Sample", "", new ConfigDescription("Click to sample sex data", null, new ConfigurationManagerAttributes { CustomDrawer = MyDrawer2 }));
            clientlistener = new Thread(ReceiveClient);
            clientlistener.Start();
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
            GUILayout.BeginHorizontal();
            if (cycle)
            {
                if (GUILayout.Button("start normal resampled "))
                {
                    start_sampled = true;
                    scanning_mode = 0;
                    cycle = false;
                }
                else if (GUILayout.Button("start bisexual resampled "))
                {
                    start_sampled = true;
                    scanning_mode = 0;
                    cycle = false;
                }
            }
            else
            {

                if (GUILayout.Button("start normal sampled "))
                {
                    start_sampled = true;
                    scanning_mode = 0;
                    cycle = false;
                }
                else if (GUILayout.Button("start bisexual sampled ")) {
                    start_sampled = true;
                    scanning_mode = 0;
                    cycle = false;
                }

            }
            GUILayout.EndVertical();
        }

        public string FloatToTimeString(float value)
        {
            int minutes = (int)(value / 60);
            int seconds = (int)(value % 60);
            int milliseconds = (int)((value - (int)value) * 100);

            return $"{minutes:D2}:{seconds:D2}.{milliseconds:D2}";
        }

        public float TimeStringToFloat(string timeString)
        {
            string[] parts = timeString.Split(':');
            int minutes = int.Parse(parts[0]);
            string[] secondsParts = parts[1].Split('.');
            int seconds = int.Parse(secondsParts[0]);
            int milliseconds = int.Parse(secondsParts[1]);

            return minutes * 60 + seconds + milliseconds / 100.0f;
        }


        [HarmonyPostfix]
        [HarmonyPatch(typeof(SceneLoadScene), "LoadScene")]
        public static void Getscene_path(SceneLoadScene __instance, string _path)
        {
            Debug.Log("New scene Start!\n");
            Debug.Log($"path:{_path}");
            cycle = false;
            scene_path = _path;
            resampled = true;
            string target_path = scene_path.Replace("/UserData/studio/scene/", "").Replace(".png", "").Replace(currentDirectory, "").Replace("/CharaStudio_Data/..", "");
            string filePath = (currentDirectory + "/UserData/KK_osr_sr6_link/" + target_path + ".txt").Replace("/UserData//studio/scene/", "");

            if (File.Exists(filePath) && Timeline.Timeline.isPlaying)
            {
                string message = $"{filePath}|{0}|{0.1}";
                byte[] data = Encoding.UTF8.GetBytes(message);
                try
                {
                    clientSocket.Send(data);
                }
                catch
                {
                    Debug.Log("Osr2 sr6 Server close.");
                    clientSocket.Close();
                    link = false;
                }
            }
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

        public string FindRootObjectPath(string rootName, string targetName)
        {
            GameObject rootObject = GameObject.Find(rootName);
            if (rootObject == null)
            {
                Logger.LogInfo($"Root object '{rootName}' not found.");
                return null;
            }

            Transform targetTransform = rootObject.GetComponentsInChildren<Transform>(true)
                .FirstOrDefault(t => t.name == targetName);

            if (targetTransform == null)
            {
                Logger.LogInfo($"Target object '{targetName}' not found under '{rootName}'.");
                return null;
            }

            List<string> pathParts = new List<string>();
            while (targetTransform != rootObject.transform)
            {
                pathParts.Add(targetTransform.name);
                targetTransform = targetTransform.parent;
            }
            pathParts.Add(rootObject.name);

            pathParts.Reverse();
            return string.Join("/", pathParts.ToArray());
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



        public float[] Dis_angle_blowjob(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 p5, Vector3 p6, Vector3 p7) //penis mouth earL earR head maleL maleR.
        {

            float dis = Vector3.Dot(p2 - p1, (p2 - p1).normalized);

            float[] results = Get_position(p2, p1, p6, p7);//vagina,penis,maleL,maleR.

            float surge = results[0];

            float sway = results[1];

            float twist_angle = Twist_angle(p3, p4, p1, p6, p7);

            float roll_angle = Roll_angle(p2, p5, p6, p7);

            float pitch_angle = Pitch_angle(p2, p5, p6, p7);

            return new float[] { dis, surge, sway, twist_angle, roll_angle, pitch_angle };
        }

        public float[] Dis_angle_breastsex(Vector3 p1, Vector3 p3, Vector3 p4, Vector3 p5, Vector3 p6, Vector3 p7, Vector3 p8, Vector3 p9) //penis femaleL femaleR head maleL maleR breastL breastR. 
        {

            Vector3 p2 = p8 + p9;

            float dis = Vector3.Dot(p2 - p1, (p2 - p1).normalized);

            float[] results = Get_position(p2, p1, p6, p7);//vagina,penis,maleL,maleR.

            float surge = results[0];

            float sway = results[1];

            float twist_angle = Twist_angle(p8, p9, p1, p6, p7);

            float roll_angle = Roll_angle(p2, p5, p6, p7);

            float pitch_angle = Pitch_angle(p2, p5, p6, p7);

            return new float[] { dis, surge, sway, twist_angle, roll_angle, pitch_angle };
        }

        public float[] Dis_angle_handjob(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 p6, Vector3 p7) //penis hand0 hand1 hand2 maleL maleR.
        {


            float dis = Vector3.Dot(p2 - p1, (p2 - p1).normalized);

            float[] results = Get_position(p2, p1, p6, p7);//vagina,penis,maleL,maleR.

            float surge = results[0];

            float sway = results[1];

            float twist_angle = Twist_angle(p2, p4, p1, p6, p7);


            float roll_angle = Roll_angle(p3, p4, p6, p7);

            float pitch_angle = Pitch_angle(p3, p4, p6, p7);

            return new float[] { dis, surge, sway, twist_angle, roll_angle, pitch_angle };
        }

        public float[] Dis_angle_handjobR(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 p6, Vector3 p7) //penis hand0 hand1 hand2 maleL maleR.
        {


            float dis = Vector3.Dot(p2 - p1, (p2 - p1).normalized);

            float[] results = Get_position(p2, p1, p6, p7);//vagina,penis,maleL,maleR.

            float surge = results[0];

            float sway = results[1];

            float twist_angle = Twist_angle(p2, p4, p1, p6, p7);


            float roll_angle = Roll_angle(p3, p4, p6, p7);

            float pitch_angle = Pitch_angle(p3, p4, p6, p7);

            return new float[] { dis, surge, sway, twist_angle, roll_angle, pitch_angle };
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

            float[] position = { surge, sway };
            return position;
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
            float dotProduct = Vector3.Dot(p1 - p2, p4 - p5);
            if ((-0.00001 < dotProduct && dotProduct <= 0) || (0 < dotProduct && dotProduct <= 0.00001)) { dotProduct = last_twist; }
            last_twist = dotProduct;
            if (angle > 90) { angle = 180 - angle; }
            if (dotProduct > 0) { angle = -angle; }
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
            if (dotProduct < 0) { angle = 180 - angle; }
            if (angle > 90) { angle -= 90; }
            else { angle = -(90 - angle); }
            return angle;
        }




        private void Clear_list()
        {
            inserts.Clear();
            surges.Clear();
            sways.Clear();
            twists.Clear();
            pitchs.Clear();
            rolls.Clear();
            play_times.Clear();
            blowjob_inserts.Clear();
            blowjob_surges.Clear();
            blowjob_sways.Clear();
            blowjob_twists.Clear();
            blowjob_pitchs.Clear();
            blowjob_rolls.Clear();
            breastsex_inserts.Clear();
            breastsex_surges.Clear();
            breastsex_sways.Clear();
            breastsex_twists.Clear();
            breastsex_pitchs.Clear();
            breastsex_rolls.Clear();
            handjobL_inserts.Clear();
            handjobL_surges.Clear();
            handjobL_sways.Clear();
            handjobL_twists.Clear();
            handjobL_pitchs.Clear();
            handjobL_rolls.Clear();
            handjobR_inserts.Clear();
            handjobR_surges.Clear();
            handjobR_sways.Clear();
            handjobR_twists.Clear();
            handjobR_pitchs.Clear();
            handjobR_rolls.Clear();
        }
        private void Setting_range()
        {
            if (interval_time > 1 || interval_time < 0.1) { interval_time = 0.1; }
            if (last_interval_time != interval_time) { resampled = true; last_interval_time = interval_time; }
            if (server_port.Value < 0 || server_port.Value > 9999) { server_port.Value = 8000; }
        }




        public void Update() {
            if (scene_path != "no") {
                Setting_range();
                if (start_sampled)
                {
                    Collect_data();
                }
                else
                {
                    if (link)
                    {
                        string target_path = scene_path.Replace("/UserData/studio/scene/", "").Replace(".png", "").Replace(currentDirectory, "").Replace("/CharaStudio_Data/..", "");
                        string filePath = (currentDirectory + "/UserData/KK_osr_sr6_link/" + target_path + ".txt").Replace("/UserData//studio/scene/", "");
                        if (File.Exists(filePath) && Timeline.Timeline.isPlaying)
                        {
                            int index = 0;
                            roundedPlaybackTime = (int)(Math.Round(Timeline.Timeline.playbackTime, 1) * 10);
                            roundedIntervalTime = (int)(Math.Round(interval_time, 1) * 10);
                            if (roundedPlaybackTime == last_roundedPlaybackTime) { return; }
                            last_roundedPlaybackTime = roundedPlaybackTime;
                            if (roundedPlaybackTime == 0 || roundedPlaybackTime >= roundedIntervalTime)
                            {
                                if (roundedPlaybackTime == 0) { index = 0; }
                                else if (roundedPlaybackTime >= roundedIntervalTime)
                                {
                                    if (roundedPlaybackTime % roundedIntervalTime == 0) { index = roundedPlaybackTime / roundedIntervalTime; }
                                }
                            }
                            //Logger.LogInfo("index:" + index);
                            string message = $"{filePath}|{index}|{interval_time}";
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

        public void Collect_data()
        {

            string target_path = scene_path.Replace("/UserData/studio/scene/", "").Replace(".png", "").Replace(currentDirectory, "").Replace("/CharaStudio_Data/..", "");
            string filePath = (currentDirectory + "/UserData/KK_osr_sr6_link/" + target_path + ".txt").Replace("/UserData//studio/scene/", "");
            try { File.Delete(filePath); } catch { }
            if (Timeline.Timeline.isPlaying)
            {
                Timeline.Timeline.Pause();
            }
            if (resampled)
            {
                female_charas.Clear();
                male_charas.Clear();
                charas.Clear();
                Studio.GuideObjectManager guideObjectManager = Singleton<Studio.GuideObjectManager>.Instance;
                Dictionary<Transform, GuideObject> dicGuideObject = Traverse.Create(guideObjectManager) .Field("dicGuideObject").GetValue<Dictionary<Transform, GuideObject>>();
                for (int i = 0; i < charas_num.Value; i++)
                {
                    string female_chara = "chaF_00" + i.ToString();
                    GameObject female_chara_root = GameObject.Find(female_chara);

                    if (female_chara_root != null)
                    {
                        GuideObject female_guideObject = dicGuideObject[female_chara_root.transform];
                        GuideBase[] female_guide = Traverse.Create(female_guideObject).Field("guide").GetValue<GuideBase[]>();
                        GuideSelect female_guideSelect = female_guide[11] as GuideSelect;
                        String chara_name = female_guideSelect.treeNodeObject.textName;
                        female_guideSelect = null;
                        female_charas.Add(female_chara_root, chara_name);   
                        charas.Add(female_chara_root, chara_name);
                    }
                    string male_chara = "chaM_00" + i.ToString();
                    GameObject male_chara_root = GameObject.Find(male_chara);
                    if (male_chara_root != null)
                    {
                        GuideObject male_guideObject = dicGuideObject[male_chara_root.transform];
                        GuideBase[] male_guide = Traverse.Create(male_guideObject).Field("guide").GetValue<GuideBase[]>();
                        GuideSelect female_guideSelect = male_guide[11] as GuideSelect;
                        String chara_name = female_guideSelect.treeNodeObject.textName;
                        female_guideSelect = null;
                        male_charas.Add(male_chara_root, chara_name);
                        charas.Add(male_chara_root, chara_name);
                    }
                }
                foreach (KeyValuePair<GameObject, String> kvp in charas)
                {
                    Logger.LogInfo($"chara__name:{kvp.Value}.chara_gameobject:{kvp.Key.name}");
                }
                Timeline.Timeline.Seek(0);
                resampled = false;
                last_playtime = 0;
                action_list.Clear();
                foreach (KeyValuePair<GameObject, String> female_chara in female_charas)
                {
                    foreach (KeyValuePair<GameObject, String> male_chara in male_charas)
                    {
                        Action_data data = new Action_data();
                        data.charas_name =  $"{female_chara.Value}({female_chara.Key.name})-{male_chara.Value}({male_chara.Key.name})" ;
                        data.inserts = new List<float>();
                        data.surges = new List<float>();
                        data.sways = new List<float>();
                        data.twists = new List<float>();
                        data.rolls = new List<float>();
                        data.pitchs = new List<float>();
                        data.blowjob_inserts = new List<float>();
                        data.blowjob_surges = new List<float>();
                        data.blowjob_sways = new List<float>();
                        data.blowjob_twists = new List<float>();
                        data.blowjob_rolls = new List<float>();
                        data.blowjob_pitchs = new List<float>();
                        data.breastsex_inserts = new List<float>();
                        data.breastsex_surges = new List<float>();
                        data.breastsex_sways = new List<float>();
                        data.breastsex_twists = new List<float>();
                        data.breastsex_rolls = new List<float>();
                        data.breastsex_pitchs = new List<float>();
                        data.handjobL_inserts = new List<float>();
                        data.handjobL_surges = new List<float>();
                        data.handjobL_sways = new List<float>();
                        data.handjobL_twists = new List<float>();
                        data.handjobL_rolls = new List<float>();
                        data.handjobL_pitchs = new List<float>();
                        data.handjobR_inserts = new List<float>();
                        data.handjobR_surges = new List<float>();
                        data.handjobR_sways = new List<float>();
                        data.handjobR_twists = new List<float>();
                        data.handjobR_rolls = new List<float>();
                        data.handjobR_pitchs = new List<float>();
                        data.bodywidths = new List<float>();
                        action_list.Add(data);
                    }
                }
                play_times.Clear();
            }
            Logger.LogInfo("playbackTime:" + Timeline.Timeline.playbackTime);
            if (Math.Round(last_playtime, 3) != Math.Round(Timeline.Timeline.playbackTime, 3))
            {
                Logger.LogInfo("Due to playtime have changed dramatically,restart compute!Please not change playtime when first compute.");
                resampled = true;
                return;
            }
            if ((float)Math.Round(Timeline.Timeline.playbackTime + interval_time, 3) < Timeline.Timeline.duration)
            {
                Timeline.Timeline.Seek((float)Math.Round(Timeline.Timeline.playbackTime + interval_time, 3));
                last_playtime = Math.Round(last_playtime, 3) + Math.Round(interval_time, 3);
            }
            else { Timeline.Timeline.Seek(Timeline.Timeline.duration); }
            play_times.Add(Math.Round(last_playtime, 3));
            if (scanning_mode == 0)
            {
                foreach (KeyValuePair<GameObject, String> female_chara in female_charas)
                {
                    female = female_chara.Key.name;
                    femaleRoot = female_chara.Key;
                    foreach (KeyValuePair<GameObject, String> male_chara in male_charas)
                    {
                        male = male_chara.Key.name;
                        maleRoot = male_chara.Key;
                        foreach (Action_data data in action_list)
                        {
                            if (data.charas_name == $"{female_chara.Value}({female_chara.Key.name})-{male_chara.Value}({male_chara.Key.name})" )
                            {
                                femalehead = GameObject.Find(FindRootObjectPath(female, "cf_j_head"));

                                femalethightL = GameObject.Find(FindRootObjectPath(female, "cf_j_thigh00_L"));

                                femalethightR = GameObject.Find(FindRootObjectPath(female, "cf_j_thigh00_R"));

                                femalehips = GameObject.Find(FindRootObjectPath(female, "cf_j_hips"));

                                femaleearL = GameObject.Find(FindRootObjectPath(female, "a_n_earrings_L"));

                                femaleearR = GameObject.Find(FindRootObjectPath(female, "a_n_earrings_R"));

                                femalemouth = GameObject.Find(FindRootObjectPath(female, "a_n_mouth"));

                                femalebreastL = GameObject.Find(FindRootObjectPath(female, "k_f_munenipL_00"));

                                femalebreastR = GameObject.Find(FindRootObjectPath(female, "k_f_munenipR_00"));

                                femalehand0L = GameObject.Find(FindRootObjectPath(female, "a_n_hand_L"));

                                femalehand1L = GameObject.Find(FindRootObjectPath(female, "a_n_ind_L"));

                                femalehand2L = GameObject.Find(FindRootObjectPath(female, "a_n_mid_L"));

                                femalehand0R = GameObject.Find(FindRootObjectPath(female, "a_n_hand_R"));

                                femalehand1R = GameObject.Find(FindRootObjectPath(female, "a_n_ind_R"));

                                femalehand2R = GameObject.Find(FindRootObjectPath(female, "a_n_mid_R"));

                                vagina = GameObject.Find(FindRootObjectPath(female, "a_n_kokan"));

                                penis = GameObject.Find(FindRootObjectPath(male, "a_n_dan"));

                                malehips = GameObject.Find(FindRootObjectPath(male, "cf_j_hips"));

                                malethightL = GameObject.Find(FindRootObjectPath(male, "cf_j_thigh00_L"));

                                malethightR = GameObject.Find(FindRootObjectPath(male, "cf_j_thigh00_R"));

                                malehead = GameObject.Find(FindRootObjectPath(male, "cf_j_head"));

                                Vector3 offset = penis.transform.position - vagina.transform.position;

                                Vector3 _vagina = vagina.transform.position + offset;
                                Vector3 _femalehps = femalehips.transform.position + offset;
                                Vector3 __vagina = (femalethightL.transform.position + femalethightR.transform.position) / 2 + offset;


                                float dis = Vector3.Distance(penis.transform.position, vagina.transform.position);
                                float[] postiton = Get_position(vagina.transform.position, penis.transform.position, malethightL.transform.position, malethightR.transform.position);
                                float surge = postiton[0];
                                float sway = postiton[1];
                                float twist_angle = Twist_angle(femalethightL.transform.position, femalethightR.transform.position, penis.transform.position, malethightL.transform.position, malethightR.transform.position);
                                float roll_angle = Roll_angle(__vagina, _femalehps, malethightL.transform.position, malethightR.transform.position);
                                float pitch_angle = Pitch_angle(_vagina, _femalehps, malethightL.transform.position, malethightR.transform.position);

                                float[] blowjob = Dis_angle_blowjob(penis.transform.position, femalemouth.transform.position, femaleearL.transform.position, femaleearR.transform.position, femalehead.transform.position, malethightL.transform.position, malethightR.transform.position);
                                float[] breastsex = Dis_angle_breastsex(penis.transform.position, femalethightL.transform.position, femalethightR.transform.position, femalehead.transform.position, malethightL.transform.position, malethightR.transform.position, femalebreastL.transform.position, femalebreastR.transform.position);
                                float[] handjobL = Dis_angle_handjob(penis.transform.position, femalehand0L.transform.position, femalehand1L.transform.position, femalehand2L.transform.position, malethightL.transform.position, malethightR.transform.position);
                                float[] handjobR = Dis_angle_handjob(penis.transform.position, femalehand0R.transform.position, femalehand1R.transform.position, femalehand2R.transform.position, malethightL.transform.position, malethightR.transform.position);
                                float blowjob_insert = blowjob[0];
                                float blowjob_surge = blowjob[1];
                                float blowjob_sway = blowjob[2];
                                float blowjob_twist = blowjob[3];
                                float blowjob_roll = blowjob[4];
                                float blowjob_pitch = blowjob[5];
                                float breastsex_insert = breastsex[0];
                                float breastsex_surge = breastsex[1];
                                float breastsex_sway = breastsex[2];
                                float breastsex_twist = breastsex[3];
                                float breastsex_roll = breastsex[4];
                                float breastsex_pitch = breastsex[5];
                                float handjobL_insert = handjobL[0];
                                float handjobL_surge = handjobL[1];
                                float handjobL_sway = handjobL[2];
                                float handjobL_twist = handjobL[3];
                                float handjobL_roll = handjobL[4];
                                float handjobL_pitch = handjobL[5];
                                float handjobR_insert = handjobR[0];
                                float handjobR_surge = handjobR[1];
                                float handjobR_sway = handjobR[2];
                                float handjobR_twist = handjobR[3];
                                float handjobR_roll = handjobR[4];
                                float handjobR_pitch = handjobR[5];
                                float bodywidth = Vector3.Distance(femalethightL.transform.position, femalethightR.transform.position) * 3;
                                if (pitch_angle < 0) { surge = -surge; }
                                if (roll_angle < 0) { sway = -sway; }
                                if (!cycle)
                                {
                                    data.inserts.Add(dis);
                                    data.surges.Add(surge);
                                    data.sways.Add(sway);
                                    data.twists.Add(twist_angle);
                                    data.rolls.Add(roll_angle);
                                    data.pitchs.Add(pitch_angle);
                                    data.blowjob_inserts.Add(blowjob_insert);
                                    data.blowjob_surges.Add(blowjob_surge);
                                    data.blowjob_sways.Add(blowjob_sway);
                                    data.blowjob_twists.Add(blowjob_twist);
                                    data.blowjob_rolls.Add(blowjob_roll);
                                    data.blowjob_pitchs.Add(blowjob_pitch);
                                    data.breastsex_inserts.Add(breastsex_insert);
                                    data.breastsex_surges.Add(breastsex_surge);
                                    data.breastsex_sways.Add(breastsex_sway);
                                    data.breastsex_twists.Add(breastsex_twist);
                                    data.breastsex_rolls.Add(breastsex_roll);
                                    data.breastsex_pitchs.Add(breastsex_pitch);
                                    data.handjobL_inserts.Add(handjobL_insert);
                                    data.handjobL_surges.Add(handjobL_surge);
                                    data.handjobL_sways.Add(handjobL_sway);
                                    data.handjobL_twists.Add(handjobL_twist);
                                    data.handjobL_rolls.Add(handjobL_roll);
                                    data.handjobL_pitchs.Add(handjobL_pitch);
                                    data.handjobR_inserts.Add(handjobR_insert);
                                    data.handjobR_surges.Add(handjobR_surge);
                                    data.handjobR_sways.Add(handjobR_sway);
                                    data.handjobR_twists.Add(handjobR_twist);
                                    data.handjobR_rolls.Add(handjobR_roll);
                                    data.handjobR_pitchs.Add(handjobR_pitch);
                                    data.bodywidths.Add(bodywidth);                            
                                }
                            }
                        }
                    }
                }
                string fileDir = Path.GetDirectoryName(filePath);
                if (!Directory.Exists(fileDir))
                {
                    Directory.CreateDirectory(fileDir);
                }
                if (Timeline.Timeline.playbackTime == Timeline.Timeline.duration)
                {
                    cycle = true;
                    start_sampled = false;
                    Logger.LogInfo("finish!!!!!!!!!\n\n\n\n");
                    using (StreamWriter writer = File.CreateText(filePath))
                    {
                        writer.WriteLine("New");
                        foreach (Action_data data in action_list)
                        {
                            writer.WriteLine(data.charas_name);
                            Logger.LogInfo(data.inserts.Count());
                            for (int i = 0; i < data.inserts.Count(); i++)
                            {
                                writer.WriteLine(
                                        data.inserts[i] + "/"
                                        + data.surges[i] + "/"
                                        + data.sways[i] + "/"
                                        + data.twists[i] + "/"
                                        + data.rolls[i] + "/"
                                        + data.pitchs[i] + "/"
                                        + play_times[i] + "/"
                                        + Timeline.Timeline.duration + "/"
                                        + data.bodywidths[i] + "/"
                                        + data.blowjob_inserts[i] + "/"
                                        + data.blowjob_surges[i] + "/"
                                        + data.blowjob_sways[i] + "/"
                                        + data.blowjob_twists[i] + "/"
                                        + data.blowjob_rolls[i] + "/"
                                        + data.blowjob_pitchs[i] + "/"
                                        + data.breastsex_inserts[i] + "/"
                                        + data.breastsex_surges[i] + "/"
                                        + data.breastsex_sways[i] + "/"
                                        + data.breastsex_twists[i] + "/"
                                        + data.breastsex_rolls[i] + "/"
                                        + data.breastsex_pitchs[i] + "/"
                                        + data.handjobL_inserts[i] + "/"
                                        + data.handjobL_surges[i] + "/"
                                        + data.handjobL_sways[i] + "/"
                                        + data.handjobL_twists[i] + "/"
                                        + data.handjobL_rolls[i] + "/"
                                        + data.handjobL_pitchs[i] + "/"
                                        + data.handjobR_inserts[i] + "/"
                                        + data.handjobR_surges[i] + "/"
                                        + data.handjobR_sways[i] + "/"
                                        + data.handjobR_twists[i] + "/"
                                        + data.handjobR_rolls[i] + "/"
                                        + data.handjobR_pitchs[i] + "/"
                                        );
                            }
                        }
                    }
                }
            }
        }
             
        


        private void ReceiveClient()
        {
            while (!end)
            {
                if (autorelink.Value) { Link_server(); }
                if (clientSocket != null && clientSocket.Connected)
                {
                    try
                    {
                        int bytesRead = clientSocket.Receive(buffer);
                        string receivedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                        string[] get = receivedData.Split(':');
                        int way = (int)int.Parse(get[0]);
                        if (way == 0)
                        {
                            if (Timeline.Timeline.isPlaying) { Timeline.Timeline.Pause(); }
                            else { Timeline.Timeline.Play(); }
                        }
                        else if (way == 1)
                        {
                            float settime = (float)0.1 * float.Parse(get[1]);
                            Timeline.Timeline.Seek(settime);
                        }
                        else if (way == 2)
                        {
                            string chara = get[1];    
                            int rootStart = chara.IndexOf("chaF_");
                            if (rootStart == -1)
                            {
                                rootStart = chara.IndexOf("chaM_");
                                if (rootStart == -1)
                                {
                                    Logger.LogInfo("cannot find chaF_ or chaM_");
                                    return;
                                }
                            }

                            if (rootStart + 8 > chara.Length)
                            {
                                Logger.LogInfo("chara data Error");
                                return;
                            }
                            string chara_root = chara.Substring(rootStart, 8);

                            GameObject chara_object = GameObject.Find(chara_root);
                            Studio.GuideObjectManager guideObjectManager = Singleton<Studio.GuideObjectManager>.Instance;
                            if (guideObjectManager != null && chara_object != null)
                            {
                                Dictionary<Transform, GuideObject> dicGuideObject = Traverse.Create(guideObjectManager).Field("dicGuideObject").GetValue<Dictionary<Transform, GuideObject>>();
                                GuideObject chara_guideObject = dicGuideObject[chara_object.transform];
                                GuideBase[] chara_guide = Traverse.Create(chara_guideObject).Field("guide").GetValue<GuideBase[]>();
                                GuideSelect chara_guideSelect = chara_guide[11] as GuideSelect;
                                chara_guideSelect.treeNodeObject.Select();
                                chara_guideSelect = null;
                            }
                           
                        }
                        else if (way == 3) {
                            string charas = get[1];//Kyoka Jiro(chaF_001)-Haruno Chika(chaM_001)
                            int femaleRootStart = charas.IndexOf("chaF_");
                            if (femaleRootStart == -1) { Logger.LogInfo("chaF_ not found in input."); return; }
                            string femalechara_root = charas.Substring(femaleRootStart, 8);

                            int maleRootStart = charas.IndexOf("chaM_");
                            if (maleRootStart == -1) { Logger.LogInfo("chaM_ not found in input."); return; }
                            string malechara_root = charas.Substring(maleRootStart, 8);
                            GameObject femalechara_object = GameObject.Find(femalechara_root);
                            GameObject malechara_object = GameObject.Find(malechara_root);
                            Studio.GuideObjectManager guideObjectManager = Singleton<Studio.GuideObjectManager>.Instance;
                            if (guideObjectManager != null && femalechara_object != null && malechara_object != null)
                            {
                                Dictionary<Transform, GuideObject> dicGuideObject = Traverse.Create(guideObjectManager).Field("dicGuideObject").GetValue<Dictionary<Transform, GuideObject>>();
                                GuideObject femalechara_guideObject = dicGuideObject[femalechara_object.transform];
                                GuideObject malechara_guideObject = dicGuideObject[malechara_object.transform];
                                GuideBase[] femalechara_guide = Traverse.Create(femalechara_guideObject).Field("guide").GetValue<GuideBase[]>();
                                GuideBase[] malechara_guide = Traverse.Create(malechara_guideObject).Field("guide").GetValue<GuideBase[]>();
                                GuideSelect femalechara_guideSelect = femalechara_guide[11] as GuideSelect;
                                GuideSelect malechara_guideSelect = malechara_guide[11] as GuideSelect;
                                femalechara_guideSelect.treeNodeObject.SetVisible(true);
                                malechara_guideSelect.treeNodeObject.SetVisible(true);
                                femalechara_guideSelect = null;
                                malechara_guideSelect = null;
                            }
                        }
                        
                        else if (way == 4)
                        {
                            string charas = get[1];//Kyoka Jiro(chaF_001)-Haruno Chika(chaM_001)
                            int femaleRootStart = charas.IndexOf("chaF_");
                            if (femaleRootStart == -1) { Logger.LogInfo("chaF_ not found in input."); return; }
                            string femalechara_root = charas.Substring(femaleRootStart, 8);

                            int maleRootStart = charas.IndexOf("chaM_");
                            if (maleRootStart == -1) { Logger.LogInfo("chaM_ not found in input."); return; }
                            string malechara_root = charas.Substring(maleRootStart, 8);
                            GameObject femalechara_object = GameObject.Find(femalechara_root);
                            GameObject malechara_object = GameObject.Find(malechara_root);
                            Studio.GuideObjectManager guideObjectManager = Singleton<Studio.GuideObjectManager>.Instance;
                            if (guideObjectManager != null && femalechara_object != null && malechara_object != null)
                            {
                                Dictionary<Transform, GuideObject> dicGuideObject = Traverse.Create(guideObjectManager).Field("dicGuideObject").GetValue<Dictionary<Transform, GuideObject>>();
                                GuideObject femalechara_guideObject = dicGuideObject[femalechara_object.transform];
                                GuideObject malechara_guideObject = dicGuideObject[malechara_object.transform];
                                GuideBase[] femalechara_guide = Traverse.Create(femalechara_guideObject).Field("guide").GetValue<GuideBase[]>();
                                GuideBase[] malechara_guide = Traverse.Create(malechara_guideObject).Field("guide").GetValue<GuideBase[]>();
                                GuideSelect femalechara_guideSelect = femalechara_guide[11] as GuideSelect;
                                GuideSelect malechara_guideSelect = malechara_guide[11] as GuideSelect;
                                femalechara_guideSelect.treeNodeObject.SetVisible(false);
                                malechara_guideSelect.treeNodeObject.SetVisible(false);
                                femalechara_guideSelect = null;
                                malechara_guideSelect = null;
                            }
                        }                        
                    }
                    catch { }
                }
            }
        }


        void OnDestroy()
        {
            end = true;
        }

    }


}

