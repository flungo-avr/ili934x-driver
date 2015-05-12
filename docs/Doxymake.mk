# The MIT License (MIT)
#
# Copyright (c) 2015, Fabrizio Lungo <fab@lungo.co.uk>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CLEAN_FIND_OPTS               = -mindepth 1 -maxdepth 1
CLEAN_FIND_ACTION             = -exec rm -r {} \;
HTML_CLEAN_EXCLUDE            = '.git*'
HTML_CLEAN_EXCLUDE_FIND_ARGS  = $(addprefix ! -name , $(HTML_CLEAN_EXCLUDE))
LATEX_CLEAN_EXCLUDE           = '.git*'
LATEX_CLEAN_EXCLUDE_FIND_ARGS = $(addprefix ! -name , $(LATEX_CLEAN_EXCLUDE))
GIT_REMOTE_ORIGIN_URL         = $(shell git config --get remote.origin.url)
GIT_CURRENT_BRANCH            = $(shell git rev-parse --abbrev-ref HEAD)
GIT_HMTL_BRANCH               = gh-pages
GIT_LATEX_BRANCH              = latex

html:
	$(info Creating directory for HTML Documentation)
	mkdir html

latex:
	$(info Creating directory for LaTeX Documentation)
	mkdir latex

.PHONY: clean-docs clean-html clean-latex

clean-docs: clean-html clean-latex

clean-html: | html
	$(info Cleaning HTML Documentation)
	@find html $(CLEAN_FIND_OPTS) $(HTML_CLEAN_EXCLUDE_FIND_ARGS) $(CLEAN_FIND_ACTION)

clean-latex: | latex
	$(info Cleaning LaTeX Documentation)
	@find latex $(CLEAN_FIND_OPTS) $(HTML_CLEAN_EXCLUDE_FIND_ARGS) $(CLEAN_FIND_ACTION)


ifeq ($(GIT_CURRENT_BRANCH),master)
%/.git: | %
	$(info Initialising git submodule for $(@D))
	git submodule init $(@D)
	git submodule update $(@D)
endif

.PHONY: docs doxygen

docs: clean-html clean-latex doxygen

doxygen: docs/Doxyfile html latex docs/DoxygenLayout.xml
	$(info Generating Documentation using Doxygen)
	@doxygen $<

.PHONY: GIT_LAST_COMMIT

GIT_LAST_COMMIT: GIT_LAST_COMMIT = $(shell git rev-parse HEAD)

.PHONY: docs-commit-prep docs-commit html-commit latex-commit

docs-commit-prep:
	$(info Checking state of git repository)
	@[ $(GIT_CURRENT_BRANCH) == master ] || (echo "FAILURE: Must be on master branch"; exit 1;)
	@git diff --no-ext-diff --quiet --exit-code || (echo "FAILURE: Unstaged changes"; exit 2;)
	@git diff-index --cached --quiet HEAD --  || (echo "FAILURE: Uncommited changes"; exit 3;)
	@! git ls-files --others --exclude-standard --error-unmatch -- ':/*' >/dev/null 2>/dev/null || (echo "FAILURE: Untracked changes"; exit 4;)

docs-commit: html-commit latex-commit

html-commit: | docs-commit-prep html/.git docs GIT_LAST_COMMIT
	$(info Commiting HTML documentation to $(GIT_HMTL_BRANCH))
	@cd html && git add . && git commit -m "Docs generated for $(GIT_LAST_COMMIT)"
	git add html && git commit -m "HTML documentation updated for $(GIT_LAST_COMMIT)"

latex-commit: | docs-commit-prep latex/.git docs GIT_LAST_COMMIT
	$(info Commiting HTML documentation to $(GIT_HMTL_BRANCH))
	@cd latex && git add . && git commit -m "Docs generated for $(GIT_LAST_COMMIT)"
	git add latex && git commit -m "LaTeX documentation updated for $(GIT_LAST_COMMIT)"
