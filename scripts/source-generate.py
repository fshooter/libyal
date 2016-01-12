#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Script to automate generation of source of the libyal libraries."""

from __future__ import print_function
import abc
import argparse
import json
import string
import os
import sys

try:
  import ConfigParser as configparser
except ImportError:
  import configparser  # pylint: disable=import-error


class ProjectConfiguration(object):
  """Class that defines a project configuration."""

  def __init__(self):
    """Initializes a project configuation object."""
    super(ProjectConfiguration, self).__init__()
    self.project_authors = None
    self.project_copyright = None

    self.library_name = None
    self.library_description = None
    self.exported_types = None

  def _GetConfigValue(self, config_parser, section_name, value_name):
    """Retrieves a value from the config parser.

    Args:
      config_parser: the configuration parser (instance of ConfigParser).
      section_name: the name of the section that contains the value.
      value_name: the name of the value.

    Returns:
      An object containing the value.
    """
    return json.loads(config_parser.get(section_name, value_name))

  def ReadFromFile(self, filename):
    """Reads the configuration from file.

    Args:
      filename: a string containing the filename.
    """
    # TODO: replace by:
    # config_parser = configparser. ConfigParser(interpolation=None)
    config_parser = configparser.RawConfigParser()
    config_parser.read([filename])

    self.project_authors = self._GetConfigValue(
        config_parser, u'Project', u'authors')
    self.project_copyright = self._GetConfigValue(
        config_parser, u'Project', u'copyright')

    self.library_name = self._GetConfigValue(
        config_parser, u'Library', u'name')
    self.library_description = self._GetConfigValue(
        config_parser, u'Library', u'description')
    self.exported_types = self._GetConfigValue(
        config_parser, u'Library', u'exported_types')

  def GetTemplateMappings(self):
    """Retrieves the template mappings.

    Returns:
      A dictionary containing the string template mappings.
    """
    template_mappings = {
        u'authors': u', '.join(self.project_authors),
        u'copyright': self.project_copyright,

        u'library_name': self.library_name,
        u'library_name_upper_case': self.library_name.upper(),
        u'library_description': self.library_description,
    }
    return template_mappings


class FunctionPrototype(object):
  """Class that defines a function prototype.

  Attributes:
    arguments: a list of strings containing the arguments.
    name: a string containing the name.
    return_type: a string containing the return type.
  """

  def __init__(self, name, return_type):
    """Initializes a function prototype.

    Args:
      name: a string containing the name.
      return_type: a string containing the return type.
    """
    super(FunctionPrototype, self).__init__()
    self.arguments = []
    self.name = name
    self.return_type = return_type

  def AddArgument(self, argument):
    """Adds an argument to the function prototype.

    Args:
      argument: a string containing the argument.
    """
    self.arguments.append(argument)


class IncludeHeaderFile(object):
  """Class that defines an include header file.

  Attributes:
    functions: a list of function prototype objects (instances of
               FunctionPrototype).
    name: a string containing the name.
  """

  def __init__(self, path):
    """Initializes an include header file.

    Args:
      path: a string containing the path.
    """
    super(IncludeHeaderFile, self).__init__()
    self._path = path

    self.name = os.path.basename(path)
    self.functions = []

  def ReadFunctions(self, project_configuration):
    """Reads the functions from the include header file.

    Args:
      project_configuration: the project configuration (instance of
                             ProjectConfiguration).

    Returns:
      A boolean to indicate the functions were read from the file.
    """
    self.functions = []

    define_extern = b'{0:s}_EXTERN'.format(
        project_configuration.library_name.upper())

    in_define_extern = False
    function_prototype = None
    with open(self._path, 'rb') as file_object:
      for line in file_object.readlines():
        line = line.strip()
        if in_define_extern:
          line = line.decode(u'ascii')

          if function_prototype:
            # Get the part of the line before the ','.
            argument, _, _ = line.partition(u',')

            function_prototype.AddArgument(argument)

            if line.endswith(u' );'):
              self.functions.append(function_prototype)
              function_prototype = None
              in_define_extern = False

          else:
            # Get the part of the line before the library name.
            return_type, _, _ = line.parition(
                project_configuration.library_name)

            # Get the part of the line after the return type.
            line = line[len(return_type):]
            return_type = return_type.strip()

            # Get the part of the remainder of the line before the '('.
            name, _, _ = line.partition(u'(')

            function_prototype = FunctionPrototype(name, return_type)

        elif line.startswith(define_extern):
          in_define_extern = True

        elif line.startswith(b'#endif'):
          # TODO reset flags
          pass

        elif line.startswith(b'#if defined( HAVE_DEBUG_OUTPUT )'):
          # TODO set flag in debug output
          pass

        elif line.startswith(b'#if defined( {0:s}_HAVE_BFIO )'):
          # TODO set flag
          pass

        elif line.startswith(b'#if defined( {0:s}_HAVE_WIDE_CHARACTER_TYPE )'):
          # TODO set flag
          pass

    return True


class SourceFileGenerator(object):
  """Class that generates source files."""

  def __init__(self, template_directory):
    """Initialize the source file generator.

    Args:
      template_directory: a string containing the path of the template
                          directory.
    """
    super(SourceFileGenerator, self).__init__()
    self._template_directory = template_directory

  def _GenerateSection(
      self, template_filename, template_mappings, output_writer,
      output_filename):
    """Generates a section from template filename.

    Args:
      template_filename: a string containing the name of the template file.
      template_mpppings: a dictionary containing the template mappings, where
                         the key maps to the name of a template variable.
      output_writer: an output writer object (instance of OutputWriter).
      output_filename: string containing the name of the output file.
    """
    template_string = self._ReadTemplateFile(template_filename)
    output_data = template_string.substitute(template_mappings)
    output_writer.WriteFile(output_filename, output_data)

  def _ReadTemplateFile(self, filename):
    """Reads a template string from file.

    Args:
      filename: string containing the name of the file containing
                the template string.

    Returns:
      A template string (instance of string.Template).
    """
    file_object = open(filename, 'rb')
    file_data = file_object.read()
    file_object.close()
    return string.Template(file_data)

  @abc.abstractmethod
  def Generate(self, project_configuration, output_writer):
    """Generates the source file.

    Args:
      project_configuration: the project configuration (instance of
                             ProjectConfiguration).
      output_writer: an output writer object (instance of OutputWriter).
    """


class LibrarySourceFileGenerator(SourceFileGenerator):
  """Class that generates the library source files."""

  def Generate(self, project_configuration, output_writer):
    """Generates a library source file.

    Args:
      project_configuration: the project configuration (instance of
                             ProjectConfiguration).
      output_writer: an output writer object (instance of OutputWriter).
    """
    template_mappings = project_configuration.GetTemplateMappings()
    for directory_entry in os.listdir(self._template_directory):
      if not directory_entry.startswith(u'libyal_'):
        continue

      template_filename = os.path.join(
          self._template_directory, directory_entry)
      if not os.path.isfile(template_filename):
        continue

      # TODO: generate types in _types.h from config.
      # TODO: generate _libX.h include headers from config.

      output_filename = u'{0:s}_{1:s}'.format(
          project_configuration.library_name, directory_entry[7:])
      output_filename = os.path.join(
          project_configuration.library_name, output_filename)

      self._GenerateSection(
          template_filename, template_mappings, output_writer, output_filename)


class FileWriter(object):
  """Class that defines a file output writer."""

  def __init__(self, output_directory):
    """Initialize the output writer.

    Args:
      output_directory: string containing the path of the output directory.
    """
    super(FileWriter, self).__init__()
    self._output_directory = output_directory

  def WriteFile(self, file_path, file_data):
    """Writes the data to file.

    Args:
      file_path: string containing the path of the file to write.
      file_data: binary string containing the data to write.
    """
    self._file_object = open(file_path, 'wb')
    self._file_object.write(file_data)
    self._file_object.close()


class StdoutWriter(object):
  """Class that defines a stdout output writer."""

  def __init__(self):
    """Initialize the output writer."""
    super(StdoutWriter, self).__init__()

  def WriteFile(self, file_path, file_data):
    """Writes the data to stdout (without the default trailing newline).

    Args:
      file_path: string containing the path of the file to write.
      file_data: binary string containing the data to write.
    """
    print(u'-' * 80)
    print(u'{0: ^80}'.format(file_path))
    print(u'-' * 80)
    print(u'')
    print(file_data, end=u'')


def Main():
  argument_parser = argparse.ArgumentParser(description=(
      u'Generates source files of the libyal libraries.'))

  argument_parser.add_argument(
      u'configuration_file', action=u'store', metavar=u'CONFIGURATION_FILE',
      default='source.conf', help=u'The source generation configuration file.')

  argument_parser.add_argument(
      u'-o', u'--output', dest=u'output_directory', action=u'store',
      metavar=u'OUTPUT_DIRECTORY', default=None,
      help=u'path of the output files to write to.')

  options = argument_parser.parse_args()

  if not options.configuration_file:
    print(u'Config file missing.')
    print(u'')
    argument_parser.print_help()
    print(u'')
    return False

  if not os.path.exists(options.configuration_file):
    print(u'No such configuration file: {0:s}.'.format(
        options.configuration_file))
    print(u'')
    return False

  if options.output_directory and not os.path.exists(options.output_directory):
    print(u'No such output directory: {0:s}.'.format(options.output_directory))
    print(u'')
    return False

  project_configuration = ProjectConfiguration()
  project_configuration.ReadFromFile(options.configuration_file)

  libyal_directory = os.path.abspath(__file__)
  libyal_directory = os.path.dirname(libyal_directory)
  libyal_directory = os.path.dirname(libyal_directory)

  # TODO: generate more source files.
  # include headers
  # pyyal files
  # yal.net files
  source_files = [
      (u'libyal', LibrarySourceFileGenerator),
  ]

  for page_name, page_generator_class in source_files:
    template_directory = os.path.join(
        libyal_directory, u'data', u'source', page_name)
    source_file = page_generator_class(template_directory)

    if options.output_directory:
      output_writer = FileWriter(options.output_directory)
    else:
      output_writer = StdoutWriter()

    source_file.Generate(project_configuration, output_writer)

  # TODO: add support for Unicode templates.

  return True


if __name__ == '__main__':
  if not Main():
    sys.exit(1)
  else:
    sys.exit(0)
