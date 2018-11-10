[![Build Status](https://travis-ci.org/Optimaton/rolac.svg?branch=master)](https://travis-ci.org/Optimaton/rolac)
## rolac - role based account control
A command line utility to manage users based on role

> **Features:**
> 1. account creation, deletion, modification
> 2. chroot env for non-admin users
> 3. user lockout based on number of attempts or duration
> 4. import ssh key for passwordless transaction(login)
>
>**Usage:**
>
> ***User Mgmt Operations:***

>`rolac create "username" [user | admin]`  
>`rolac delete "username"`  
>`rolac modify "username" level [user | admin]`  
>`rolac lockout "username" [max-attempts | max-duration]`  
>`rolac copy "username" "path-to-public-key" (if the user has copied the key)`  
>`rolac copy "username" "user@remote-access-ip-address:port" (if key is not copied)`  

> More operations willbe added if I still find this interesting in future

> TODO(raghu): An user created with admin role will have elevated privileges. proxyadmin will have one less privilege than admin (although proxyadmin also is in the elevated position to run system wide commands)

WORK UNDER PROGRESS !
