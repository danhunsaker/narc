# -*- mode: ruby -*-
# vi: set ft=ruby :

# determine vagrant provider
ENV['VAGRANT_DEFAULT_PROVIDER'] = ENV['NANOBOX_BUILD_VAGRANT_PROVIDER'] || 'virtualbox'

Vagrant.configure('2') do |config|

  config.vm.box = 'ubuntu/trusty64'

  config.vm.provider 'virtualbox' do |v|
    v.memory = 1024
    v.cpus   = 1
  end

  config.vm.provider "vmware_fusion" do |v, override|
    v.vmx["memsize"] = "1024"
    v.vmx["numvcpus"] = "1"
    v.gui = false
    override.vm.box = "trusty64_vmware"
    override.vm.box_url = 'https://github.com/pagodabox/vagrant-packer-templates/releases/download/v0.2.0/trusty64_vmware.box'
  end

  config.vm.network "private_network", type: "dhcp"

  config.vm.provision "shell", inline: <<-SCRIPT
    echo "installing build tools..."
    apt-get -y update -qq
    apt-get -y upgrade
    apt-get install -y build-essential
    add-apt-repository ppa:wesmason/nodejs-backport -y
    apt-get -qq update
    apt-get install -y libuv1 libuv1-dev autoconf valgrind
    apt-get -y autoremove
  SCRIPT

end
