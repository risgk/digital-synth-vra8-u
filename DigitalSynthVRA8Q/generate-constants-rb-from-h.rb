File.open("../DigitalSynthVRA8Q/constants.h", "r") do |input|
  File.open("./constants.rb", "w") do |output|
    input.each_line do |line|
      output.puts line.chomp[16..-2]
    end
  end
end
