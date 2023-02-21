cd ~/tttt/CMSSW_10_6_26/src/tttt; cmsenv; eval $(./setup.sh env); cd -

# Data
time(rqlb doAll_data_NonAPV_2016.C > logs/doAll_data_NonAPV_2016.log 2>&1 &
rqlb doAll_data_APV_2016.C > logs/doAll_data_APV_2016.log 2>&1 &
rqlb doAll_data_2017.C > logs/doAll_data_2017.log 2>&1 &
rqlb doAll_data_2018.C > logs/doAll_data_2018.log 2>&1 &)

# MC 
time(rqlb doAll_mc_2016_NonAPV.C > logs/doAll_mc_2016_NonAPV.log 2>&1 &
rqlb doAll_mc_2016_APV.C > logs/doAll_mc_2016_APV.log 2>&1 &
rqlb doAll_mc_2017.C > logs/doAll_mc_2017.log 2>&1 &
rqlb doAll_mc_2018.C > logs/doAll_mc_2018.log 2>&1 &)

# give it time to run
echo "All histogramming scripts have begun. View the logs in logs/*"
wait 
echo "All histogramming scripts have completed. Beginning to plot..."

# plotting
time(rqlb stack_2016_NonAPV.C > logs/stack_2016_NonAPV.log 2>&1 &
rqlb stack_2016_APV.C > logs/stack_2016_APV.log 2>&1 &
rqlb stack_2017.C > logs/stack_2017.log 2>&1 &
rqlb stack_2018.C > logs/stack_2018.log 2>&1 &
rqlb stack_17_18.C > logs/stack_17_18.log 2>&1 &)

# give it time to run
echo "All plotting scripts have begun. View the logs in logs/*"
wait
echo "All plotting scripts have completed."
