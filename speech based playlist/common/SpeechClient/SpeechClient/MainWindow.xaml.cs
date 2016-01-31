using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Media;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;

namespace SpeechClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        string recfilerecogtxt;
        string recfilerecogwav;
        string recfiletrainwav;
        string recfiletraintxt;
        int timerecog;
        int statebuttontrain;
        int statebuttonrecog;
        int counter;
        int maxrec;
        string final;
        List<double> vadarray;
        List<double> energyarray;
        List<double> finalarray;
        List<int> selarray;
        double thresh;
        double threshfactor;
        int selcounter;

        public MainWindow()
        {
            InitializeComponent();
            threshfactor = 0.2;
        }


        private void Button_Click(object sender, RoutedEventArgs e)//train
        {
            buttonaddrecord.IsEnabled = false;
            buttondetect.IsEnabled = false;
            buttonrecog.IsEnabled = false;
            buttontrain.IsEnabled = false;
            starttrain(1);
        }
       
        private void Button_Click_1(object sender, RoutedEventArgs e) /// recognize;
        {
            switch (statebuttonrecog)
            {
                case 1:
                    buttontrain.IsEnabled = false;
                    buttonrecog.Content = "Record";
                    text1.Text = "Press  record button for recording the uttrance for 3 seconds ";
                    statebuttonrecog = 2;
                    break;

                case 2:
                    startrec(recfilerecogwav,recfilerecogtxt, 1);
                    buttontrain.IsEnabled = false;
                    buttonrecog.Content = "Play";
                    text1.Text = "Press  Play button to hear the recording ";
                    statebuttonrecog = 3;
                    break;

                case 3:
                    playsound(recfilerecogwav,1);
                    buttontrain.IsEnabled = false;
                    buttonrecog.Content = "Next";
                    text1.Text = "Press  Next button for recognition ";
                    statebuttonrecog = 4;
                    break;

                case 4:
                    vad(recfilerecogtxt,1);
                    startrecog();
                    buttontrain.IsEnabled = false;
                    buttonrecog.Content = "Finish";
                    text1.Text = "You said " + final.ToString();
                    statebuttonrecog = 7;
                    break;

                default:
                    deletefiles();
                    buttontrain.IsEnabled = true;
                    buttonrecog.Content = "Recognize";
                    buttontrain.IsEnabled = true;
                    buttontrain.Content = "Train";
                    text1.Text = "Please Press Recognize to start speech recognition     Train for Training The System  ";
                    statebuttonrecog = 1;
                    break;
            }
        }

        private void lodedfn(object sender, RoutedEventArgs e)
        {
            recfilerecogtxt = @"E:\common\output\test\4_";
            recfilerecogwav = @"E:\common\output\testwav\4_";
            recfiletraintxt = @"E:\common\input\4_";
            recfiletrainwav = @"E:\common\inputwav\4_";
            statebuttonrecog = 1;
            statebuttontrain = 1;
            deletefiles();
            counter = 1;
            maxrec = 31;
            timerecog = 2;
            vadarray=new List<double>();
            energyarray = new List<double>();
            finalarray = new List<double>();
            selarray = new List<int>();
            combox123.Visibility = Visibility.Hidden;
            selcounter = 22;
          
        }


    
        public void playsound(string str ,int input)
        {
            string current = str + input.ToString()+".wav";
            using (SoundPlayer player = new SoundPlayer(current))
            {
                player.PlaySync();
            }
        }

        public void playmusic(string inp)
        {
             using (SoundPlayer player = new SoundPlayer(inp))
            {
                player.PlaySync();
            }
        }

        public void startrec(string inputwav ,string inputtxt , int abc)
        {
            string currenttextfile = inputtxt + abc.ToString() + ".txt";
            string currentwavfile = inputwav + abc.ToString() + ".wav";
            string final = " " + timerecog.ToString() +" "+ currentwavfile + " " + currenttextfile;
            ProcessStartInfo start = new ProcessStartInfo();
            start.Arguments = final;
            // Enter the executable to run, including the complete path
            start.FileName = @"E:\common\Record.exe";
            start.WindowStyle = ProcessWindowStyle.Hidden;
            start.CreateNoWindow = true;
            int exitCode;
            // Run the external process & wait for it to finish
            using (Process proc = Process.Start(start))
            {
                proc.WaitForExit();

                // Retrieve the app's exit code
                exitCode = proc.ExitCode;
            }
        }
        public void deletefiles()
        {
            Array.ForEach(Directory.GetFiles(@"E:\common\output\test\"), delegate(string path) { File.Delete(path); });
            Array.ForEach(Directory.GetFiles(@"E:\common\output\testwav\"), delegate(string path) { File.Delete(path); });
        }
        public int startrecog()
        {
            int aaa;
            ProcessStartInfo start = new ProcessStartInfo();
            start.FileName = @"E:\common\testing.exe";
            using (Process proc = Process.Start(start))
            {
                proc.WaitForExit();
                // Retrieve the app's exit code
                aaa = proc.ExitCode;
                getfinal(aaa);
                return aaa;
            }

        }
        public int startrecogasync()
        {
            ProcessStartInfo start = new ProcessStartInfo();
            start.FileName = @"E:\common\testing.exe";
            using (Process proc = Process.Start(start))
            {
                proc.WaitForExit();
                // Retrieve the app's exit code
                return proc.ExitCode;
            }

        }

        public async void getfinal(int abc)
        {
            switch (abc)
            {

                case 0:
                    final = "Asmaeese";
                    playmusic(@"e:\songs\assamese.wav");
                    break;
                case 1:
                     final = "Bengali";
                     playmusic(@"e:\songs\bengali.wav");
                    break;
                case 2:
                     final = "English";
                     playmusic(@"e:\songs\english.wav");
                    break;
                case 3:
                    final = "Hindi";
                    playmusic(@"e:\songs\hindi.wav");
                    break;
                case 4:
                    final = "Marathi";
                    playmusic(@"e:\songs\marathi.wav");
                    break;
                case 5:
                    final = "Oriya";
                    playmusic(@"e:\songs\odia.wav");
                    break;
                default:
                    final="Not Recognised";
                    break;
            }
        }

        public async void gettext(int abc)
        {
            switch (abc)
            {

                case 0:
                    final = "Asmaeese";
                    break;
                case 1:
                    final = "Bengali";
                    break;
                case 2:
                    final = "English";
                    break;
                case 3:
                    final = "Hindi";
                    break;
                case 4:
                    final = "Marathi";
                    break;
                case 5:
                    final = "Oriya";
                    break;
                default:
                    final = "Not Recognised";
                    break;
            }
        }

        public void vad(string inptxt1 , int abc)
        {
            int start = 0;
            string curr = inptxt1 + abc.ToString() + ".txt";
            thresh = 0;
            int cnt = 0;
            double temp =0;
            using (StreamReader r = new StreamReader(curr))
            {
                string line;
                while ((line = r.ReadLine()) != null)
                {
                    vadarray.Add(Convert.ToDouble(line));
                }
            }
                while (cnt < vadarray.Count)
                {
                    temp = vadarray[cnt] * vadarray[cnt];
                    energyarray.Add(temp);
                    cnt++;
                }
                cnt = 0;
                temp = 0;
                while (cnt < energyarray.Count)
                {
                    temp += energyarray[cnt];
                    cnt++;
                }
                thresh = temp / energyarray.Count;
                /////
                thresh *= threshfactor; ;
                ////
                cnt = 0;
                temp = 0;
                while (cnt < vadarray.Count)
                {
                    if (energyarray[cnt] > thresh && start == 0)
                    {
                        finalarray.Add(vadarray[cnt]);
                        start = 1;
                    }
                    if (energyarray[cnt] > thresh && start == 1)
                    {
                      
                        finalarray.Add(vadarray[cnt]);
                        start = 1;
                    }
                    if (energyarray[cnt] < thresh && start == 1)
                    {
                        start = 0;
                    }
                    cnt++;
                }
                write(curr);   
        }

        public void write(string abc)
        {
            File.Delete(abc);
            TextWriter tw = new StreamWriter(abc);
            foreach (double s in finalarray)
                tw.WriteLine(s.ToString());
            tw.Close();
            vadarray.Clear();
            finalarray.Clear();
            energyarray.Clear();
        }
        public void writecounter()
        {
            TextWriter tw = new StreamWriter(@"E:\common\config\counter.txt");
            foreach (int s in selarray)
                tw.WriteLine(s.ToString());
            tw.Close();
            
        }

        public void starttrain(int abc)
        {
            ProcessStartInfo start = new ProcessStartInfo();
            // Enter the executable to run, including the complete path
            start.FileName = @"E:\common\training.exe";
            // Do you want to show a console window?
            int exitCode;
            // Run the external process & wait for it to finish
            using (Process proc = Process.Start(start))
            {
                proc.WaitForExit();
                // Retrieve the app's exit code
                exitCode = proc.ExitCode;
            }

        }

        public void autorec()
        {
            int temp123;
            while(true)
            {
                    deletefiles();
                    this.Dispatcher.Invoke((Action)(() =>{
                     text1.Text = "Listining Mode ";
                    text1.Background = System.Windows.Media.Brushes.Green; 
                    }));
                    Thread.Sleep(100);
                    startrec(recfilerecogwav, recfilerecogtxt, 1);
                    vad(recfilerecogtxt,1);
                    this.Dispatcher.Invoke((Action)(() =>{
                        text1.Text = "Analysing Mode ";
                        text1.Background = System.Windows.Media.Brushes.IndianRed;
                    }));
                    temp123 =startrecogasync();
                    gettext(temp123);
                    Thread.Sleep(100);
                    this.Dispatcher.Invoke((Action)(() =>
                    {
                        text1.Text = "PLAY MODE : " +final;
                        text1.Background = System.Windows.Media.Brushes.Indigo;
                    }));
                    getfinal(temp123);
                    Thread.Sleep(500);
            }
        }

        private void buttondetect_Click(object sender, RoutedEventArgs e)
        {
            buttonrecog.IsEnabled = false;
            buttontrain.IsEnabled = false;
            buttondetect.IsEnabled = false;
            Task.Factory.StartNew(() =>
            {
                autorec();
            });
        }

        public void initaddnew()
        {
            buttondetect.IsEnabled = false;
            buttonrecog.IsEnabled = false;
            buttontrain.IsEnabled = false;
            using (StreamReader r = new StreamReader(@"E:\common\config\counter.txt"))
            {
                string line;
                while ((line = r.ReadLine()) != null)
                {
                    selarray.Add(Convert.ToInt32(line));
                }
                r.Close();
            }
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)///add recording
        {
            string intxt;
            string inwav;
            switch (selcounter)
            {
                case 0:
                    File.WriteAllText(@"E:\common\config\counter.txt", "");
                    selarray[0] += 1;
                    intxt = @"E:\common\input\0_";
                    inwav = @"E:\common\inputwav\0_";
                    MessageBox.Show("Adding Assamese new training file No "+selarray[0].ToString()+". Starting recoring for 2 seconds on pressing OK");
                    startrec(inwav,intxt, selarray[0]);
                    vad(intxt, selarray[0]);
                    writecounter();
                    MessageBox.Show("Recording Done");
                    break;
                case 1:
                    File.WriteAllText(@"E:\common\config\counter.txt", "");
                    selarray[1] += 1;
                    intxt = @"E:\common\input\1_";
                    inwav = @"E:\common\inputwav\1_";
                    MessageBox.Show("Adding Bengali new training file No " + selarray[1].ToString() + ". Starting recoring for 2 seconds on pressing OK");
                    startrec(inwav, intxt, selarray[1]);
                    vad(intxt, selarray[1]);
                    writecounter();
                    MessageBox.Show("Recording Done");
                    break;
                case 2:
                    File.WriteAllText(@"E:\common\config\counter.txt", "");
                    selarray[2] += 1;
                    intxt = @"E:\common\input\2_";
                    inwav = @"E:\common\inputwav\2_";
                    MessageBox.Show("Adding English new training file No " + selarray[2].ToString() + ". Starting recoring for 2 seconds on pressing OK");
                    startrec(inwav, intxt, selarray[2]);
                    vad(intxt, selarray[2]);
                    writecounter();
                    MessageBox.Show("Recording Done");
                    break;
                case 3:
                    File.WriteAllText(@"E:\common\config\counter.txt", "");
                    selarray[3] += 1;
                    intxt = @"E:\common\input\3_";
                    inwav = @"E:\common\inputwav\3_";
                    MessageBox.Show("Adding Hindi new training file No " + selarray[3].ToString() + ". Starting recoring for 2 seconds on pressing OK");
                    startrec(inwav, intxt, selarray[3]);
                    vad(intxt, selarray[3]);
                    writecounter();
                    MessageBox.Show("Recording Done");
                    break;
                case 4:
                    File.WriteAllText(@"E:\common\config\counter.txt", "");
                    selarray[4] += 1;
                    intxt = @"E:\common\input\4_";
                    inwav = @"E:\common\inputwav\4_";
                    MessageBox.Show("Adding Hindi new training file No " + selarray[4].ToString() + ". Starting recoring for 2 seconds on pressing OK");
                    startrec(inwav, intxt, selarray[4]);
                    vad(intxt, selarray[4]);
                    writecounter();
                    MessageBox.Show("Recording Done");
                    break;
                case 5:
                    File.WriteAllText(@"E:\common\config\counter.txt", "");
                    selarray[5] += 1;
                    intxt = @"E:\common\input\5_";
                    inwav = @"E:\common\inputwav\5_";
                    MessageBox.Show("Adding Hindi new training file No " + selarray[5].ToString() + ". Starting recoring for 2 seconds on pressing OK");
                    startrec(inwav, intxt, selarray[5]);
                    vad(intxt, selarray[5]);
                    writecounter();
                    MessageBox.Show("Recording Done");
                    break;
                case 22:
                    combox123.Visibility = Visibility.Visible;
                    MessageBox.Show("Select Language from Drop Down Menu");
                    initaddnew();
                    break;
                default:
                    break;
            }
            
        }

        private void combochange(object sender, SelectionChangedEventArgs e)
        {
            selcounter = combox123.SelectedIndex;
        }
       
    }

}
