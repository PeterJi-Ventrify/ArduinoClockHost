using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Globalization;
using System.IO.Ports;

namespace Winform_Demo
{
    public partial class Form1 : Form
    {
        int cnt = 0;
        int time = 0;
        int[] baudrates = { 1200, 2400, 4800, 9600, 19200, 57600, 115200 };
        string[] ports;
        DateTime dateTime;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Upon loading the window, search for serial ports
            // And add them to the drop down list
            ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                comboBox2.Items.Add(port);
            }
            // Fill comboBox1 with common baudrates
            foreach (int baudrate in baudrates)
            {
                comboBox1.Items.Add(baudrate);
            }
            // Set the default baudrate
            comboBox1.SelectedItem = 115200;
            // Set the defualt COM port to the last added
            comboBox2.SelectedIndex = ports.Length - 1;
            // Initilaze 
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            cnt++;
            if (cnt == time)
            {
                timer1.Stop();
                button1.Text = "Start";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text == "Connect")
            {
                // When Connect is clicked, set serial port parameters
                // and establish connection
                serialPort1.PortName = comboBox2.Text;
                serialPort1.BaudRate = (int)comboBox1.SelectedItem;
                serialPort1.Open();
                button1.Text = "Disconnect";
                timer2.Start();
            }
            else
            {
                serialPort1.Close();
                button1.Text = "Connect";
                timer2.Stop();
            }
            
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            // Update label6 with current date and time\
            dateTime = DateTime.Now;
            label6.Text = Convert.ToString(dateTime) + Convert.ToString(dateTime.DayOfWeek);
            // Send the string over serialPort1
            if (serialPort1.IsOpen) serialPort1.Write(label6.Text);
            else button1_Click(sender, e);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            ports = SerialPort.GetPortNames();
            comboBox2.Items.Clear();
            foreach (string port in ports)
            {
                comboBox2.Items.Add(port);
            }
            comboBox2.SelectedIndex = ports.Length - 1;
        }
    }
}
