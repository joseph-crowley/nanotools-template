import json
import subprocess
import logging
import uproot
from concurrent.futures import ThreadPoolExecutor, as_completed

# Global variables to control file and directory paths
file_to_add = 'mc.json'
INPUT_DIR = "../cpp/outputs/mc/"
INPUT_SUFFIX = "hists_"
OUTPUT_DIR = INPUT_DIR 
OUTPUT_SUFFIX = INPUT_SUFFIX

# setup logging
logging.basicConfig(filename='add_categories.log', filemode='w', level=logging.INFO)
log = logging.getLogger(__name__)

def validate_json(file_name):
    """Validate the json file structure and contents"""
    try:
        with open(file_name, 'r') as f:
            sample_map = json.load(f)
            if not isinstance(sample_map, dict):
                log.error("Invalid json file. Expecting a dictionary")
                return False
            for key, value in sample_map.items():
                if not isinstance(value, list):
                    log.error("Invalid json file. Expecting a list of samples for each category")
                    return False
        return True
    except json.decoder.JSONDecodeError as e:
        log.error("Invalid json file. Error: %s", e)
        return False
    except FileNotFoundError as e:
        log.error("File not found. Error: %s", e)
        return False
    except Exception as e:
        log.error("An error occurred while validating json file. Error: %s", e)
        return False

def add_histograms(cat, samples):
    """Function to add histograms for a given category and samples"""
    input_files = []
    for s in samples:
        input_file = "{}{}{}.root".format(INPUT_DIR, INPUT_SUFFIX, s)
        try:
            uproot.open(input_file)
            input_files.append(input_file)
        except FileNotFoundError as e:
            log.error("File not found %s. Error: %s", input_file, e)
        except Exception as e:
            log.error("An error occurred while opening file %s. Error: %s", input_file, e)
    if not input_files:
        log.error("No input files found for category %s", cat)
        return
    output_file = "{}{}{}.root".format(OUTPUT_DIR, OUTPUT_SUFFIX, cat)
    try:
        subprocess.run(["hadd", "-f", output_file] + input_files)
        log.info("Successfully added histograms for category %s", cat)
    except Exception as e:
        log.error("An error occurred while adding histograms for category %s. Error: %s", cat, e)

if __name__ == "__main__":
    if validate_json(file_to_add):
        with open(file_to_add,'r') as f:
            sample_map = json.load(f)

        with ThreadPoolExecutor() as executor:
            futures = [executor.submit(add_histograms, cat, samples) for cat, samples in sample_map.items()]
            for future in as_completed(futures):
                future.result()
        log.info("Adding histograms completed successfully")
    else:
        log.error("Adding histograms failed")

