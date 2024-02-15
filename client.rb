require 'socket'
starttime = Process.clock_gettime(Process::CLOCK_MONOTONIC)

s = TCPSocket.new 'localhost', 8000

s.write("testfiles/#{ARGV[0]}.txt\n")

s.each_line do |line|
    #puts line
end

s.close

endtime = Process.clock_gettime(Process::CLOCK_MONOTONIC)
elapsedtime = endtime - starttime
puts "Done in #{elapsedtime}"