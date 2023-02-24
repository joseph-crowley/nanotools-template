cd ~/tttt/CMSSW_10_6_26/src/tttt; cmsenv; eval $(./setup.sh env); cd -

# back up the logs/ and output/ directories if they exist
if [ -d logs/ ] && [ -d outputs/ ]; then
    # backup the existing directories
    backup_num=$(ls -d logs_backup_* | wc -l)
    mkdir "logs_backup_$backup_num"
    mv logs/ "logs_backup_$backup_num/"
    mkdir "outputs_backup_$backup_num"
    mv outputs/ "outputs_backup_$backup_num/"
fi

# create the logs/ and outputs/ directories if they don't exist
mkdir -p logs/
mkdir -p outputs/ outputs/data outputs/mc outputs/plots

# create the log files so that 'tail -f logs/*' works  
touch logs/compile_scripts.log

touch logs/doAll_data_NonAPV_2016.log
touch logs/doAll_data_APV_2016.log
touch logs/doAll_data_2017.log
touch logs/doAll_data_2018.log

touch logs/doAll_mc_NonAPV_2016.log
touch logs/doAll_mc_APV_2016.log
touch logs/doAll_mc_2017.log
touch logs/doAll_mc_2018.log

touch logs/stack_2016_NonAPV.log
touch logs/stack_2016_APV.log
touch logs/stack_2017.log
touch logs/stack_2018.log


# Compile the macro
#rqlb compile_scripts.C > logs/compile_scripts.log 2>&1 
rm analyze_bjets_C.so
rm directory_tools_C.so
root -l -b -q -e .L analyze_bjets.C+ > logs/compile_scripts.log 2>&1 
root -l -b -q -e .L directory_tools.C+ > logs/compile_scripts.log 2>&1 

# Make Histograms: Data
rqlb doAll_data_NonAPV_2016.C > logs/doAll_data_NonAPV_2016.log 2>&1 &
rqlb doAll_data_APV_2016.C > logs/doAll_data_APV_2016.log 2>&1 &
rqlb doAll_data_2017.C > logs/doAll_data_2017.log 2>&1 &
rqlb doAll_data_2018.C > logs/doAll_data_2018.log 2>&1 &

# Make Histograms: MC
rqlb doAll_mc_2016_NonAPV.C > logs/doAll_mc_2016_NonAPV.log 2>&1 &
rqlb doAll_mc_2016_APV.C > logs/doAll_mc_2016_APV.log 2>&1 &
rqlb doAll_mc_2017.C > logs/doAll_mc_2017.log 2>&1 &
rqlb doAll_mc_2018.C > logs/doAll_mc_2018.log 2>&1 &

# give it time to run
echo "All histogramming scripts have begun. View the logs in logs/*"
wait 
echo "All histogramming scripts have completed. Beginning to plot..."

# Plotting the Histograms 
rqlb stack_2016_NonAPV.C > logs/stack_2016_NonAPV.log 2>&1 &
rqlb stack_2016_APV.C > logs/stack_2016_APV.log 2>&1 &
rqlb stack_2017.C > logs/stack_2017.log 2>&1 &
rqlb stack_2018.C > logs/stack_2018.log 2>&1 &
#rqlb stack_17_18.C > logs/stack_17_18.log 2>&1 &

# give it time to run
echo "All plotting scripts have begun. View the logs in logs/*"
wait
echo "All plotting scripts have completed."
