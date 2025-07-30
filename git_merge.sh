#!/bin/bash

# Git automation script for minishell project
# Usage: ./git_merge.sh "commit message" [branch_name]
# Default branch to merge is current branch if not specified

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_step() {
    echo -e "${BLUE}[STEP]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Check if commit message is provided
if [ -z "$1" ]; then
    print_error "Please provide a commit message"
    echo "Usage: $0 \"commit message\" [branch_name]"
    exit 1
fi

COMMIT_MESSAGE="$1"
CURRENT_BRANCH=$(git branch --show-current)
MERGE_BRANCH="${2:-$CURRENT_BRANCH}"

print_step "Starting git workflow..."
echo "Current branch: $CURRENT_BRANCH"
echo "Branch to merge into dev: $MERGE_BRANCH"
echo "Commit message: $COMMIT_MESSAGE"
echo

# Step 1: Add all changes
print_step "Adding all changes..."
if git add .; then
    print_success "All changes added"
else
    print_error "Failed to add changes"
    exit 1
fi

# Step 2: Commit changes
print_step "Committing changes..."
if git commit -m "$COMMIT_MESSAGE"; then
    print_success "Changes committed"
else
    print_warning "Nothing to commit or commit failed"
fi

# Step 3: Push current branch
print_step "Pushing $CURRENT_BRANCH..."
if git push; then
    print_success "Push to $CURRENT_BRANCH successful"
else
    print_error "Failed to push $CURRENT_BRANCH"
    exit 1
fi

# Step 4: Checkout dev
print_step "Switching to dev branch..."
if git checkout dev; then
    print_success "Switched to dev branch"
else
    print_error "Failed to checkout dev branch"
    exit 1
fi

# Step 5: Pull latest dev (optional but recommended)
print_step "Pulling latest dev changes..."
if git pull; then
    print_success "Dev branch updated"
else
    print_warning "Failed to pull dev changes (continuing anyway)"
fi

# Step 6: Merge the specified branch
print_step "Merging $MERGE_BRANCH into dev..."
if git merge "$MERGE_BRANCH"; then
    print_success "Merge successful"
else
    print_error "Merge failed - please resolve conflicts manually"
    exit 1
fi

# Step 7: Push dev
print_step "Pushing dev branch..."
if git push; then
    print_success "Dev branch pushed successfully"
else
    print_error "Failed to push dev branch"
    exit 1
fi

# Step 8: Return to original branch (if different from dev)
if [ "$CURRENT_BRANCH" != "dev" ]; then
    print_step "Returning to $CURRENT_BRANCH..."
    if git checkout "$CURRENT_BRANCH"; then
        print_success "Returned to $CURRENT_BRANCH"
    else
        print_warning "Failed to return to $CURRENT_BRANCH - currently on dev"
    fi
fi

echo
print_success "Git workflow completed successfully! 🎉"
echo "Summary:"
echo "  - Committed: '$COMMIT_MESSAGE'"
echo "  - Merged: $MERGE_BRANCH -> dev"
echo "  - Current branch: $(git branch --show-current)"
