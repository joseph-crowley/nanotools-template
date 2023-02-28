# keep track of runtimes
start_time=$(date +%s)

# set up the environment
cd ~/tttt/CMSSW_10_6_26/src/tttt; cmsenv; eval $(./setup.sh env); cd -

# specify file directory for the input root files
current_date=$(date +%Y_%m_%d)

export FILEDIR="/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230223_tt_bkg_Cutbased"
export PLOTDIR="/home/users/crowley/public_html/tttt/${current_date}_analyze_bjets_stacked_Cutbased"
#export FILEDIR="/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230225_tt_bkg_MVA"
#export PLOTDIR="/home/users/crowley/public_html/tttt/${current_date}_analyze_bjets_stacked_MVA"

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
mkdir -p outputs/ outputs/code outputs/data outputs/mc outputs/plots

# create the log files so that 'tail -f logs/*' works  
touch logs/compile_scripts.log

#touch logs/doAll_data_NonAPV_2016.log
#touch logs/doAll_data_APV_2016.log
#touch logs/doAll_data_2017.log
touch logs/doAll_data_2018.log

#touch logs/doAll_mc_NonAPV_2016.log
#touch logs/doAll_mc_APV_2016.log
#touch logs/doAll_mc_2017.log
touch logs/doAll_mc_2018.log

#touch logs/stack_2016_NonAPV.log
#touch logs/stack_2016_APV.log
#touch logs/stack_2017.log
touch logs/stack_2018.log

# keep track of runtimes
setup_time=$(date +%s)
elapsed_time=$((setup_time-start_time))
echo "Setup took $elapsed_time seconds."


# Compile the macro
echo "Compiling scripts..."
rm analyze_bjets_C.so
rm directory_tools_C.so
cp analyze_bjets.C outputs/code/.
cp directory_tools.C outputs/code/.
cp doAll_*_20*.C outputs/code/.
cp stack_20*.C outputs/code/.
cp doAll_everything.sh outputs/code/.
root -l -b -q -e .L analyze_bjets.C+ > logs/compile_scripts.log 2>&1 
root -l -b -q -e .L directory_tools.C+ >> logs/compile_scripts.log 2>&1 

# keep track of runtimes
compilation_time=$(date +%s)
elapsed_time=$((compilation_time-setup_time))
echo "Compilation took $elapsed_time seconds."
echo ""


# Make Histograms: Data
echo "Starting histogramming scripts..."
#root -q -l -b doAll_data_NonAPV_2016.C > logs/doAll_data_NonAPV_2016.log 2>&1 &
#root -q -l -b doAll_data_APV_2016.C > logs/doAll_data_APV_2016.log 2>&1 &
#root -q -l -b doAll_data_2017.C > logs/doAll_data_2017.log 2>&1 &
root -q -l -b doAll_data_2018.C > logs/doAll_data_2018.log 2>&1 &

# Make Histograms: MC
#root -q -l -b doAll_mc_2016_NonAPV.C > logs/doAll_mc_2016_NonAPV.log 2>&1 &
#root -q -l -b doAll_mc_2016_APV.C > logs/doAll_mc_2016_APV.log 2>&1 &
#root -q -l -b doAll_mc_2017.C > logs/doAll_mc_2017.log 2>&1 &
root -q -l -b doAll_mc_2018.C > logs/doAll_mc_2018.log 2>&1 &

# give it time to run
echo "All histogramming scripts have begun. View the logs in logs/*"
echo ""
echo "The following output is from the background processes:"
wait 

# keep track of runtimes
histogramming_time=$(date +%s)
elapsed_time=$((histogramming_time-compilation_time))
echo ""
echo "All histogramming scripts completed in $elapsed_time seconds."
echo ""


# Plotting the Histograms 
echo "Beginning to plot..."
#root -q -l -b stack_2016_NonAPV.C > logs/stack_2016_NonAPV.log 2>&1 &
#root -q -l -b stack_2016_APV.C > logs/stack_2016_APV.log 2>&1 &
#root -q -l -b stack_2017.C > logs/stack_2017.log 2>&1 &
root -q -l -b stack_2018.C > logs/stack_2018.log 2>&1 &

# give it time to run
echo "All plotting scripts have begun. View the logs in logs/*"
echo ""
echo "The following output is from the background processes:"
wait

# keep track of runtimes
plotting_time=$(date +%s)
elapsed_time=$((plotting_time-histogramming_time))
echo ""
echo "All plotting scripts have completed in $elapsed_time seconds."
echo ""

finish_time=$(date +%s)
elapsed_time=$((finish_time-start_time))
echo "Full processing took $elapsed_time seconds."
