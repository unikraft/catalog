using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Program
{
    static void Main()
    {
        int port = 8080;
        TcpListener server = null;
        try
        {
            server = new TcpListener(IPAddress.Any, port);
            server.Start();
            Console.WriteLine($"Server listening on port {port}...");

            while (true)
            {
                using TcpClient client = server.AcceptTcpClient();

                using NetworkStream stream = client.GetStream();

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);

                string request = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                Console.WriteLine("Received Request:\n" + request.Split('\n')[0]);

                string responseString;

                if (request.StartsWith("GET / HTTP/"))
                {
                    string responseBody = "Bye, World!\n";
                    responseString = $"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: {responseBody.Length}\r\nConnection: close\r\n\r\n{responseBody}";
                }
                else
                {
                    string responseBody = "404 Not Found\n";
                    responseString = $"HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: {responseBody.Length}\r\nConnection: close\r\n\r\n{responseBody}";
                }

                byte[] msg = Encoding.UTF8.GetBytes(responseString);
                stream.Write(msg, 0, msg.Length);
                client.Close();
            }
        }
        catch (Exception e)
        {
            Console.WriteLine("Exception: {0}", e);
        }
        finally
        {
            server?.Stop();
        }
    }
}

