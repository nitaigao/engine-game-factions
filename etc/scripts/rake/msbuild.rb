require 'rake'
require 'rake/tasklib'
require 'vstudioide'

require "rexml/document"

include VStudioIDE

class MSBuild
  def initialize(solutionFile, clrVersion = 'v3.5')
    @solutionFile = solutionFile
    frameworkDir = File.join(ENV['windir'].dup, 'Microsoft.NET', 'Framework', clrVersion)
    @msbuildExecutable = File.join(frameworkDir, 'msbuild.exe')
  end
  
  def clean(compileMode = 'Debug')
     # sh "#{@msbuildExecutable} #{@solutionFile} /property:Configuration=#{compileMode} /t:Clean"
  end
  
	def compile( compileMode = 'Debug' )
		
		slnFile = File.new( @solutionFile )
		slnDocument = SLNDocument.new(slnFile) 
		
		oldworkingDir = Dir.pwd
		Dir.chdir( File.dirname( @solutionFile ) )
		
		includePath = ''
		
		slnDocument.projects.each{ |project|
			
			if ( project.path.include?( 'vcproj' )  ) then
		
				projectFile = File.new( project.path )
				projectXml = REXML::Document.new projectFile
				
				compilerToolElement = projectXml.elements[ "/VisualStudioProject/Configurations/Configuration/Tool[@Name='VCCLCompilerTool']" ]
				includeAttribute = compilerToolElement.attributes[ 'AdditionalIncludeDirectories' ]
				
				if ( includeAttribute != nil ) then
				
					includePath += includeAttribute.chomp( ';' ) + ';'
				
				end
			
			end
		
		}
		
		chdir oldworkingDir
		
		vcPath = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/vcvars32.bat"
		includePath = 'set INCLUDE="%INCLUDE%;' + includePath + '"'
		
		msBuild = "#{@msbuildExecutable} #{@solutionFile} /m /verbosity:detailed /property:BuildInParallel=false /property:Configuration=#{compileMode} /property:platform=Win32 /property:VCBuildAdditionalOptions=/useenv /t:Rebuild"
		
		puts vcPath + ' & ' + includePath + ' & ' + msBuild
		
	end
end