require 'rake'
require 'rake/tasklib'

class MSBuild
  def initialize(solutionFile, clrVersion = 'v3.5')
    @solutionFile = solutionFile
    frameworkDir = File.join(ENV['windir'].dup, 'Microsoft.NET', 'Framework', clrVersion)
    @msbuildExecutable = File.join(frameworkDir, 'msbuild.exe')
  end
  
  def clean(compileMode = 'Debug')
     sh "#{@msbuildExecutable} #{@solutionFile} /property:Configuration=#{compileMode} /t:Clean"
  end
  
	def compile(compileMode = 'Debug')
	 sh "#{@msbuildExecutable} #{@solutionFile} /m /property:BuildInParallel=false /property:Configuration=#{compileMode} /property:platform=Win32 /t:Rebuild"
	end
end