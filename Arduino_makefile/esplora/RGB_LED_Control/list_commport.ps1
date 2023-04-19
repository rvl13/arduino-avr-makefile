$active_port = [System.IO.Ports.SerialPort]::getportnames()
#echo $active_port
return $active_port
