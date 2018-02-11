using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;


namespace AgCubio
{
    /// <summary>
    /// Networking class that creats a socket to connect to the server.
    /// </summary>
    public static class NetworkingCode
    {
        private static System.Text.UTF8Encoding encode = new System.Text.UTF8Encoding();

        public delegate void Callback(PreservedState PState);


        /// <summary>
        /// A method that connects to the server using both the Ip address and the port number
        /// </summary>
        /// <param name="callback"></param>
        /// <param name="Hostname"></param>
        public static void Connect_to_Server(Callback callback, string Hostname)
        {
            PreservedState pstate = new PreservedState();
            pstate.State_Socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
            pstate.State_Callback = callback;

            IPHostEntry Iphost = Dns.GetHostEntry(Hostname);
            IPAddress Ip;
            if (Hostname == "localhost")
                Ip = Iphost.AddressList[1];
            else
                Ip = Iphost.AddressList[0];

            EndPoint EP = new IPEndPoint(Ip, 11000);

            pstate.State_Socket.BeginConnect(EP, Connected_to_Server, pstate);
        }

        /// <summary>
        /// A method that ends the connection
        /// </summary>
        /// <param name="state"></param>
        private static void Connected_to_Server(IAsyncResult state)
        {
            PreservedState pstate = (state.AsyncState as PreservedState);
            try
            {
                pstate.State_Socket.EndConnect(state);
                pstate.State_Callback(pstate);
            }
            catch (Exception e)
            {
                //pstate.State_Socket.Shutdown(SocketShutdown.Both);
                pstate.State_Socket.Close();
                //pstate.State_Callback(pstate); 
            }
        }

        /// <summary>
        ///A method that uses the IAsyncResult state to save our GUIcall back for future use, constantly looping to 
        /// receive more data
        /// </summary>
        /// <param name="state"></param>
        private static void ReceiveCallback(IAsyncResult state)
        {
            PreservedState pstate = (state.AsyncState as PreservedState);
            try
            {
                int byt = pstate.State_Socket.EndReceive(state);
                lock (pstate)
                {
                    if (byt > 0)
                    {
                        pstate.data.Append(encode.GetString(pstate.buffer, 0, byt));
                        pstate.State_Callback(pstate);
                    }
                }
            }
            catch (Exception e)
            {

                //pstate.State_Socket.Shutdown(SocketShutdown.Both);
                pstate.State_Socket.Close();
                //pstate.State_Callback(pstate);
            }
        }

        /// <summary>
        ///A method that request for more data
        /// </summary>
        /// <param name="state"></param>
        public static void i_want_more_data(PreservedState state)
        {
            try
            {
                state.State_Socket.BeginReceive(state.buffer, 0, PreservedState.buffersize, 0, ReceiveCallback, state);
            }
            catch (Exception e)
            {
                //state.State_Socket.Shutdown(SocketShutdown.Both);
                state.State_Socket.Close();
                //state.State_Callback(state);
            }
        }


        /// <summary>
        /// A method that sends information to the server 
        /// </summary>
        /// <param name="socket"></param>
        /// <param name="data"></param>
        public static void Send(Socket socket, string data)
        {
            PreservedState state = new PreservedState();
            try
            {
                byte[] byteData = encode.GetBytes(data);

                state.State_Socket = socket;
                state.buffer = byteData;

                if (!(socket == null))
                {
                    state.State_Socket.BeginSend(byteData, 0, byteData.Length, 0, SendCallBack, state);
                }
            }
            catch (Exception e)
            {
                //state.State_Socket.Shutdown(SocketShutdown.Both);
                state.State_Socket.Close(); /////////////////////////////////////////////////////////////////////////////////////
                //state.State_Callback = Server.CloseConnection(); //////////////////////////////////////////////////////////////
                //state.State_Callback(state);
            }
        }

        /// <summary>
        /// checking connectivity to disconnect gracefully
        /// </summary>
        /// <param name="socket"></param>
        /// <returns></returns>
        public static bool IsConnected(Socket socket)
        {
            try
            {
                bool check1 = socket.Poll(1000, SelectMode.SelectRead);
                bool check2 = (socket.Available == 0);

                if (check1 && check2)
                    return false;
                else
                    return true;
            }
            catch (Exception e)
            {            
                return false;
            }
        }
            
            
        /// <summary>
        /// A method that ends the send infomation
        /// </summary>
        /// <param name="ar"></param>
        private static void SendCallBack(IAsyncResult ar)
        {
            PreservedState pstate = (ar.AsyncState as PreservedState);
            try
            {
                Socket New_Socket = pstate.State_Socket;
                int SendByte = New_Socket.EndSend(ar);

                if (SendByte == pstate.buffer.Length)
                {
                    // Safe to shutdown socket
                    pstate.State_Socket.Shutdown(SocketShutdown.Both);
                    pstate.State_Socket.Close();
                }
                else
                {
                    // Keep sending remaining portion
                    Send(New_Socket, encode.GetString(pstate.buffer, SendByte - 1, pstate.buffer.Length-SendByte));
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                pstate.State_Socket.Shutdown(SocketShutdown.Both);
                pstate.State_Socket.Close();
                
             
            }
        }

        /// <summary>
        /// Creates a TCPListener that will wait for any connections to the server 
        /// </summary>
        /// <param name="callback"></param>
        public static void Server_Awaiting_Client_Loop(Callback callback, int port)
        {
            //int port = 11000;
            TcpListener listener = new TcpListener(IPAddress.Any, port);
            EndPoint ep = listener.LocalEndpoint;

            PreservedState listener_state = new PreservedState(); // State for listener
            listener_state.State_Socket = listener.Server; //puts the server in the socket so that Accept_a_new_Client can access it
            listener_state.State_Callback = callback;

            listener.Start();
            listener.BeginAcceptSocket(Accept_a_New_Client, listener_state);
        }

        /// <summary>
        /// Starts the socket connection from the TCP listener and stores the socket in the state, as well as the callback.  
        /// </summary>
        /// <param name="ar"></param>
        public static void Accept_a_New_Client(IAsyncResult ar)
        {
            PreservedState listener_state = (ar.AsyncState as PreservedState);

            PreservedState pstate = new PreservedState();
            pstate.State_Socket = listener_state.State_Socket.EndAccept(ar); // A new socket is "generated" here - every socket needs a new state 
            pstate.State_Callback = listener_state.State_Callback;

            pstate.State_Callback(pstate); // Pass in the new state, let the server store it
            listener_state.State_Socket.BeginAccept(Accept_a_New_Client, listener_state);
        }
    }

    /// <summary>
    /// A class preserves callback states
    /// </summary>
    public class PreservedState
    {
        /// <summary>
        ///Buffersize stores the amount of bits we want.
        /// </summary>
        public const int buffersize = 2048;

        /// <summary>
        /// Stores sockets in the preserved state.  
        /// </summary>
        public Socket State_Socket;

        /// <summary>
        /// stores buffersize in an Array
        /// </summary>
        public byte[] buffer = new byte[buffersize];

        /// <summary>
        /// Created a string builder to store our messages
        /// </summary>
        //public string data;
        public StringBuilder data = new StringBuilder();

        /// <summary>
        ///Creates a GUI callback delegate to preserve our state
        /// </summary>
        public NetworkingCode.Callback State_Callback;
    }

}
