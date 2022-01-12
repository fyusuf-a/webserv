#!/usr/bin/env bash


# \\ ------------ GET ---------//
# \\ Request 1 // 
curl -s localhost:8001/ > Response/GET/my_resp1
# \\ Request 2 // 
curl -s localhost:8001/directory > Response/GET/my_resp2
# \\ Request 3 // 
curl -s localhost:8001/directory/youpi.bad_extension > Response/GET/my_resp3
# \\ Request 4 // 
curl -s localhost:8001/directory/youpi.bla > Response/GET/my_resp4
# \\ Request 5 // 
curl -s localhost:8001/directory/oulalala > Response/GET/my_resp5
# \\ Request 6 // 
curl -s localhost:8001/directory/nop > Response/GET/my_resp6
# \\ Request 7 // 
curl -s localhost:8001/directory/nop/ > Response/GET/my_resp7
# \\ Request 8 // 
curl -s localhost:8001/directory/nop/other.pouic > Response/GET/my_resp8
# \\ Request 9 // 
curl -s localhost:8001/directory/nop/other.pouac > Response/GET/my_resp9
# \\ Request 10 // 
curl -s localhost:8001/directory/Yeah > Response/GET/my_resp10
# \\ Request 11 // 
curl -s localhost:8001/directory/Yeah/not_happy.bad_extension > Response/GET/my_resp11


# \\ ------------ POST ---------//
# \\ Request 1 //
dd if=/dev/random of=random1.txt bs=1 count=158745
curl -v -X POST  --data-binary  @"random1.txt" -H "Transfer-Encoding: chunked" http://localhost:8002/random-output1.txt
# \\ Request 2 // 
dd if=/dev/random of=random2.txt bs=1 count=10000000
curl -v -X POST  --data-binary  @"random2.txt" -H "Transfer-Encoding: chunked" http://localhost:8002/random-output2.txt
# \\ Request 3 // 
yes this is a test | head -n 250000 > random3.txt
curl -v -X POST  --data-binary  @"random3.txt" -H "Transfer-Encoding: chunked" http://localhost:8002/random-output3.txt
# curl -s localhost:8001/directory/youpi.bla  > Response/POST/my_resp2       |  size -> 100000000
# # \\ Request 3 // 
# curl -s localhost:8001/directory/youpa.bla  > Response/POST/my_resp3       | size -> 100000000
# # \\ Request 4 // 
# curl -s localhost:8001/directory/youpi.bla > Response/POST/my_resp4        | size -> 100000000 with special header
# # \\ Request 5 // 
# curl -s localhost:8001/post_body > Response/POST/my_resp5                  | size -> 0
# # \\ Request 6 // 
# curl -s localhost:8001/post_body > Response/POST/my_resp6                  | size -> 100
# # \\ Request 7 // 
# curl -s localhost:8001/post_body > Response/POST/my_resp7                  | size -> 200
# # \\ Request 8 // 
# curl -s localhost:8001/post_body > Response/POST/my_resp8                  | size -> 101
exit 0



