#!/usr/bin/perl

use warnings;
use strict;

use HTTP::Daemon;
use HTTP::Status;
use HTTP::Response;

my $daemon = HTTP::Daemon->new(
		LocalAddr => '0.0.0.0',
		LocalPort => 8080,
	) or die;

while (my $client_connection = $daemon->accept) {
    my $request = $client_connection->get_request;
    my $response = HTTP::Response->new(200);
    $response->content("Hello, World!\r\n");
    $client_connection->send_response($response);
}
