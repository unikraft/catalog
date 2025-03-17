open Cohttp_lwt_unix

let callback _conn req _body = 
  let uri = Request.uri req in
  let response_body = "Bye, World!\n" in
  Printf.printf "Received request for resource: %s\n" (Uri.to_string uri);
  flush stdout;
  Server.respond_string ~status:`OK ~body:response_body ()

let create_server () =
  let port = 8080 in
  Printf.printf "Server starting on port %d...\n" port;
  flush stdout;
  Server.create ~mode:(`TCP (`Port port)) (Server.make ~callback ())

let () = ignore (Lwt_main.run (create_server ()))