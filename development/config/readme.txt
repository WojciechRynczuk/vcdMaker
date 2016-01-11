Use this command to format souces before integrating them(Cygwin):
astyle --options=./development/config/AstyleConfiguration.cfg $(find ./sources -name "*.[ch]*")

Use this command to create the CCCC documentation:
dir /b /s *.cpp *.c *.s | cccc -

Use Windows endings(Cygwin):
sed -i 's/\r//' $(find ./sources -name "*.*")
