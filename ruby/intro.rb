#!/usr/bin/env ruby

class MegaGreeter
    attr_accessor :names

    # Create the object
    def initialize(names = "world")
        @names = names
    end

    # say hi to everybody
    def say_hi
        if @names.nil?
            puts "..."
        elsif @names.respond_to?("each")
            # @names is a list of some kind, iterate!
            @names.each do |name|
                puts "Hello #{name}!"
            end
        else
            puts "Hello #{@names}!"
        end
    end
end

if __FILE__ == $0
    mg = MegaGreeter.new
    mg.say_hi

    mg.names = "Zeke"
    mg.say_hi

    mg.names = ["Albert", "Brenda", "Charles", "Dave", "Engelbert"]
    mg.say_hi

    mg.names = nil
    mg.say_hi
end
