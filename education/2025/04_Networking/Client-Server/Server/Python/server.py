# Import necessary modules
from http.server import BaseHTTPRequestHandler, HTTPServer  # For creating a simple HTTP server
from urllib.parse import urlparse, parse_qs                 # To parse URL query parameters
import json                                                 # To handle JSON for POST requests

# The port our server will listen on
PORT = 8080

# Dictionary to track scores for each player
# Key: player name (string)
# Value: score (integer)
scores = {}

# Function to add points to a player's score
def add_points(player, points=1):
    """
    Adds points to a player's total score.
    
    If the player does not exist in the scores dictionary,
    it starts with 0.
    
    Returns the updated score for that player.
    """
    scores[player] = scores.get(player, 0) + points
    return scores[player]

# Custom request handler for our game server
class GameHandler(BaseHTTPRequestHandler):

    # Handle GET requests (when a client sends a request like ?player=Alice)
    def do_GET(self):
        # Parse the full URL (e.g., /?player=Alice&increment=3)
        parsed_url = urlparse(self.path)
       
        # Extract query parameters into a dictionary
        # Example: {'player': ['Alice'], 'increment': ['3']}
        query_params = parse_qs(parsed_url.query)

        # Example: ?player=Alice
        #          ?player=Alice&increment=9

        # Get player name from query parameters
        # If no player is specified, use "unknown"
        player = query_params.get("player", ["unknown"])[0]
        
        # Get increment from query parameters (default = 1)
        increment = int(query_params.get("increment", [1])[0])

        # Pythagorean cup logic
        if increment > 9:
            increment = -increment

        # Add points to the player's score
        add_points(player, increment)

        # Send the updated leaderboard back to the client
        self.send_leaderboard()

    # Handle POST requests (when a client sends JSON data in the body)
    def do_POST(self):
        # Read the number of bytes in the request body
        content_length = int(self.headers.get('Content-Length', 0))

        # Read the body data
        body = self.rfile.read(content_length)
        
        try:
            # Parse JSON from the request body
            data = json.loads(body)
            
            # Extract player name and increment
            player = data.get("player", "unknown")
            increment = int(data.get("increment", 1))
            
            # Add points to the player's score
            add_points(player, increment)
        except Exception as e:
            # If JSON is invalid, respond with 400 Bad Request
            self.send_response(400)
            self.end_headers()
            self.wfile.write(f"Error parsing JSON: {e}".encode())
            return
        
        # Send updated leaderboard back to the client
        self.send_leaderboard()

    # Function to create and send the leaderboard to the client
    def send_leaderboard(self):
        # Sort the scores dictionary by score descending
        # sorted_scores is a list of tuples: [(player, score), ...]
        sorted_scores = sorted(scores.items(), key=lambda item: item[1], reverse=True)
        
        # Find the longest player name (for alignment)
        max_playername_length = max(len(playername) for playername in scores.keys()) if scores else 0
        
        # Find the longest score (for alignment)
        max_score_length = max(len(str(score)) for score in scores.values()) if scores else 0

        # Build the leaderboard with ranks (1, 2, 3, ...)
        # Names are left-justified, scores are right-justified for neat alignment
        leaderboard = [
            f"{pos}. {player.ljust(max_playername_length)} : {str(score).rjust(max_score_length)}"
            for pos, (player, score) in enumerate(sorted_scores, start=1)
        ]

        # Create a response dictionary to send as JSON
        response = {
            "status": "ok",
            "leaderboard": leaderboard
        }

        # Send HTTP response code 200 (OK)
        self.send_response(200)
        
        # Set the response content type to JSON
        self.send_header("Content-Type", "application/json")
        self.end_headers()
        
        # Convert response dictionary to JSON string and send it
        self.wfile.write((json.dumps(response) + "\n").encode())


# Create an HTTP server and tell it to use our GameHandler
httpd = HTTPServer(('0.0.0.0', PORT), GameHandler)
print(f"Server running on port {PORT}")

# Start the server and wait forever for requests
httpd.serve_forever()