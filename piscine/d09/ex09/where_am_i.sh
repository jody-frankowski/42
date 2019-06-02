ifconfig | grep 'inet ' | awk '{print $2}' || echo "I am lost!"
