#$active_port = [System.IO.Ports.SerialPort]::getportnames()

# Read the first command line argument (COMM port used by Esplora)
$ESPL = $args[0]

# Create a new comm port object with the same port and BaudRate 1200
$port= new-Object System.IO.Ports.SerialPort $ESPL,1200,None,8,one

# Try opening the opening the Comm port
$port.open()

# Not required
#$port.WriteLine("Hello world")

# immediately close the port after opening it,
# this will reset the Esplora.
$port.Close()


