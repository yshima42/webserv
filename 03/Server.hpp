#include <string>
#include <vector>

struct Location
{
	std::string name; //uri

	// Define a HTTP redirection.
	std::string root;

	// Define a list of accepted HTTP methods for the route
	std::vector< std::string > allowed_methods;

	// Set a default file to answer if the request is a directory.
	std::vector< std::string > index;

	// Execute CGI based on certain file extension (for example .php).
	std::string cgi_path;

	// Limit client body size.
	size_t client_body_size_limit;
};

struct Server
{
	// Choose the port and host of each ’server’.
	size_t port;
	std::string host;

	// Setup the server_names or not.
	std::string name; // 複数必要？ server_namesと書いてある

	// Setup default error pages.
	std::string error_page; // これも複数必要？ error pagesと書いてある

	// Setup routes with one or multiple of the following rules/configuration (routes wont be using regexp)
	std::string root;

	std::vector< Location > locations;

	// Turn on or off directory listing.
	bool directory_listing;
};

