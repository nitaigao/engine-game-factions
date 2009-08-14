require 'find'
require 'zip/zipfilesystem'
require '../etc/scripts/version'
require '../etc/scripts/rake/msbuild'

require File.expand_path('../etc/scripts/rake/msbuild')

def delete_empty_directories(root_directory)
  iterations = deleted_total = 0
  loop do # a directory containing an directory will become empty when the subdir is removed
    iterations += 1
    deleted = 0
    Dir[File.join(root_directory,'**','*')].each do |e|
      next unless File.directory?(e)
      next unless (Dir.entries(e)-['.','..']).empty?
      Dir.delete(e) # will fail if e is not, in fact, an empty dir
      deleted += 1
    end
    break if deleted.zero?
    deleted_total += deleted
  end
end

namespace :vendor do
	desc "Cleans the solution"
	task :clean do
		begin
			MSBuild.new($vendor_file).clean( $build_configuration )
		rescue Exception => e
			raise "\n\nFailed: There was an error when trying to clean the solution\n#{e}"
		end
	end
	
	desc "Builds the solution"
	task :compile do
		begin
			MSBuild.new($vendor_file).compile( $build_configuration )
		rescue Exception => e
			raise "\n\nFailed: There was an error when compiling the solution\n#{e}"
		end
	end
end

namespace :build do
	desc "Cleans the solution"
	task :clean do
		begin
			MSBuild.new($solution_file).clean( $build_configuration )
			FileUtils.rm_rf($outputdir)
		rescue Exception => e
			raise "\n\nFailed: There was an error when trying to clean the solution\n#{e}"
		end
	end
	
	desc "Builds the solution"
	task :compile do
		begin
			MSBuild.new($solution_file).compile( $build_configuration )
		rescue Exception => e
			raise "\n\nFailed: There was an error when compiling the solution\n#{e}"
		end
	end
	
	desc "Test the build output"
	task :test do
		begin
		
			
		
			Dir.glob( File.join( $outputbindir , "*Tests.exe" )  ) .each{ | test |

				system( test + ' --gtest_output=xml:\\')
			
			}
		    
		rescue Exception => e
			raise "\n\nFailed: There was an error while running tests\n#{e}"
		end
	end
end

namespace :data do
	desc "Copies all required data to the build output"
	task :build do
		begin
			game_dir = File.join( $outputdir, 'data' )
			
			FileUtils.rm_rf game_dir
			FileUtils.mkdir game_dir
			
			etc_data_dir = File.join( '..', 'etc', 'data' )
			game_data_dir = game_dir
			
			Dir.foreach( etc_data_dir ) { | dir |
				if !dir.to_s.include? "." then
				
					etc_data = File.join( etc_data_dir, dir )
					game_data = File.join( game_data_dir, dir )
					game_data_zip = game_data + '.bad'
					
					puts game_data_zip
					
					Zip::ZipFile.open(game_data_zip, Zip::ZipFile::CREATE) do |zipfile|
						Find.find(etc_data) do |path|     	
							if File.directory?(path) == false then       
								dest = path.slice(etc_data.length + 1, path.length - etc_data.length - 1)
								zipfile.add( dest, path ) if dest
							end
						end
					end
				end
			}
			
		rescue Exception => e
			raise "\n\nFailed: There was an error when copying build data\n#{e}"
		end
	end
end

namespace :deploy do
  task :store do
	begin	
		versionInfo = VersionInfo.new
		artifacts_path = $packagesdir
		output_path = File.join(artifacts_path, $packagefile)
	  
	    FileUtils.rm_rf(artifacts_path)
	    Dir.mkdir(artifacts_path)
		
		build_output_dir = $outputdir
	      
	    build_file_list = FileList.new( File.join( $outputdir,'**/*.exe' ), File.join( $outputdir,'**/*.dll' ), File.join( $outputdir,'**/*.cfg' ), File.join( $outputdir,'**/*.bad' ) )
		
		Zip::ZipFile.open(output_path, Zip::ZipFile::CREATE) do |zipfile|
	      build_file_list.each { |path|     			
			if File.directory?(path) == false then       
				dest = path.slice(build_output_dir.length + 1, path.length - build_output_dir.length - 1)
				puts "Adding #{dest} to #{output_path}"
				zipfile.add(dest,path) if dest
			end
	      }
	    end
		
	rescue Exception => e
		raise "\n\nFailed: There was an error while creating the build output\n#{e}"
	end
  end
end

$build_configuration = 'Release'
$application_name = '4ha6EW2cru'
$vendor_file = '../etc/vendor/Vendor.sln'
$solution_file = $application_name + '.sln'
$builddir = '../build'
$packagesdir = File.join( '../', 'packages' )
$packagefile = File.join( 'Factions.zip' )
$outputdir = File.join( $builddir, $build_configuration )
$outputbindir = File.join( $outputdir, 'bin' )

task :data => [ "data:build" ]
task :build => [ "build:clean", "build:compile" ]
task :vendor => ["vendor:clean", "vendor:compile"]
task :test => ["build:test"]
task :deploy => [ "deploy:store" ]
task :continuous_integration => [ :vendor, :build, :data, :test, :deploy ]
task :default => :build