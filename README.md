[![Build Status](https://travis-ci.org/raghu-veer/rolac.svg?branch=master)](https://travis-ci.org/raghu-veer/rolac)
## rolac - role based account control
A command line utility to manage users based on role

> **Features:**
> 1. account creation, deletion, modification
> 2. chroot env for non-admin users
> 3. admin user shall have all the privileges whereas proxyadmin will be a proxy  for  admin user with one less feature of not being able to do user mgmt
> 4. user lockout based on number of attempts
> 5. import ssh key for passwordless transaction(login)
>
>**Usage:**
>
> ***User Mgmt Operations:***

>`rolac create [user | admin | proxyadmin] "username"`  
>`rolac delete "username"`  
>`rolac modify "username" level [user | admin | proxyadmin]`  
>`rolac lockout "username"`  
>`rolac copy "username" "path-to-public-key" (if the user has copied the key)`  
>`rolac copy "username" "user@remote-access-ip-address:port" (if key is not copied)`  

> More operations willbe added if I still find this interesting in future

> Note: An user created with admin role will have elevated privileges. proxyadmin will have one less privilege than admin (although proxyadmin also is in the elevated position to run system wide commands)

WORK UNDER PROGRESS !

