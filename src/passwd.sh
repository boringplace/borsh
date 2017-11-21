#!/usr/bin/expect

spawn sudo /usr/bin/passwd [lindex $argv 0]
set password [lindex $argv 1]
expect "Enter new password:"
send "$password\r"
expect "Re-type new password:"
send "$password\r"
expect eof
