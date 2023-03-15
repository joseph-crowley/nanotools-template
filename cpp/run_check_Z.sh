# keep track of runtimes
start_time=$(date +%s)

# set up the environment
cd ~/tttt/CMSSW_10_6_26/src/tttt; cmsenv; eval $(./setup.sh env); cd -

# specify file directory for the input root files
current_date=$(date +%Y_%m_%d)

export FILEDIRDATA="/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230307_dilepton_Z_check_data"
export FILEDIRMC="/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230307_dilepton_Z_check_mc"

export FILEDIR="/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230307_dilepton_Z_check"
export PLOTDIR="/home/users/crowley/public_html/tttt/${current_date}_check_Z"

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

# create a README for the run
cat > logs/README << EOF
This log directory contains logs for the tttt analysis.

Run date: $(date +%Y-%m-%d)
Run time: $(date +%H:%M:%S)

Environment variables:
FILEDIR=$FILEDIR
PLOTDIR=$PLOTDIR

This script compiles and runs analysis scripts, and then plots histograms. The logs/ directory contains log files for the different steps of the analysis.

Compilation log: logs/compile_scripts.log
Data histogramming logs: logs/check_Z_data_*.log
MC histogramming logs: logs/check_Z_mc_*.log
Histogram plotting logs: logs/check_Z_stack_*.log
EOF

# create the log files so that 'tail -f logs/*' works  
touch logs/compile_scripts.log

touch logs/check_Z_data_2018.log

touch logs/check_Z_mc_2018.log

touch logs/check_Z_stack_2018.log

# keep track of runtimes
setup_time=$(date +%s)
elapsed_time=$((setup_time-start_time))
echo "Setup took $elapsed_time seconds."


# Compile the macro
echo "Compiling scripts..."
rm check_Z_C.so
rm directory_tools_C.so

# keep a copy of the code with the output
cp check_Z.C outputs/code/.
cp directory_tools.C outputs/code/.
cp check_Z_*_20*.C outputs/code/.
cp check_Z_stack_20*.C outputs/code/.
cp run_check_Z.sh outputs/code/.
root -l -b -q -e .L check_Z.C+ > logs/compile_scripts.log 2>&1 
root -l -b -q -e .L directory_tools.C+ >> logs/compile_scripts.log 2>&1 

# keep track of runtimes
compilation_time=$(date +%s)
elapsed_time=$((compilation_time-setup_time))
echo "Compilation took $elapsed_time seconds."
echo ""


# Make Histograms: Data
echo "Starting histogramming scripts..."
root -q -l -b check_Z_data_2018.C > logs/check_Z_data_2018.log 2>&1 &

# Make Histograms: MC
root -q -l -b check_Z_mc_2018.C > logs/check_Z_mc_2018.log 2>&1 &

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
root -q -l -b check_Z_stack_2018.C > logs/check_Z_stack_2018.log 2>&1 &

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
