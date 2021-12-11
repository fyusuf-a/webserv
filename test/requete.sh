#!/usr/bin/env bash

# \\ Request 1 // 
curl localhost:8001/ > Response/my_resp1

# \\ Request 2 // 
curl localhost:8001/directory > Response/my_resp2

# \\ Request 3 // 
curl localhost:8001/directory/youpi.bad_extension > Response/my_resp3

# \\ Request 4 // 
curl localhost:8001/directory/youpi.bla > Response/my_resp4

# \\ Request 5 // 
curl localhost:8001/directory/oulalala > Response/my_resp5

# \\ Request 6 // 
curl localhost:8001/directory/nop > Response/my_resp6

# \\ Request 7 // 
curl localhost:8001/directory/nop/ > Response/my_resp7

# \\ Request 8 // 
curl localhost:8001/directory/nop/other.pouic > Response/my_resp8

# \\ Request 9 // 
curl localhost:8001/directory/nop/other.pouac > Response/my_resp9

# \\ Request 10 // 
curl localhost:8001/directory/Yeah > Response/my_resp10

# \\ Request 11 // 
curl localhost:8001/directory/Yeah/not_happy.bad_extension > Response/my_resp11

exit 0



